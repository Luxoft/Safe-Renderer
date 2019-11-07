#!/usr/bin/perl

=head1 NAME
  CombineChangeLogs.pl

  Script for merging changelogs.

=head1 USAGE
  perl CombineChangeLogs.pl [--help] [--verbose] [--repo-path path]

  If the script is run without parameters, default values are used:
    --verbose      = 0 (disabled)
    --repo-path = ../..

  Optional parameters:
    --help                  Show this help message and exit
    --verbose               Verbose output
    --repo-path  path       Path to main repository folder

=head1 ALGORITHM
0. Done outside this script
  * Update 'config/DocBookConfig.ent' (set common variables: data, version, and issuer)

The following steps (1-5) are executed for the following folder:
  * doc/changelog

1. Load and initialize template
  * load 'releases/release_X.XX.X.xml' template
  * update template fields
  * remove stub 'fixed defects' and 'new features' sections

2. For each file 'drafts/defect*.xml' and 'drafts/feature*.xml' (except '*0000.xml' - those are template files):
  * append corresponding section (defect or feature) if none exists yet
  * convert description (title -> entry, para -> entry)

3. Update (create) 'releases/release_A.BC.X.xml'
  * insert stub for current version if none exists yet
  * update defects and features
  * sort releases by number

4. Update 'changelog.xml'
  * insert link to file 'releases/release_A.BC.X.xml' if none exists yet

5. Update 'revision_history.xml'
  * remove section with current release
  * append section with current release (date and release number are from 'DocBookConfig.ent' file)

=head1 TODO
  Insert verbose output.
=cut

use strict;
use warnings;
use File::Basename;
use File::Spec;
use Getopt::Long;
use Cwd qw(getcwd abs_path);
use XML::LibXML;
use XML::LibXSLT;

use constant IS_WIN => ($^O eq 'MSWin32' || $^O eq 'dos');

sub EscapePath {
    my $path = shift;
    $path = '"' . $path . '"'
        if $path =~ m/ /;
    return $path;
}

sub ChdirHelper {
    my $folder = shift;
    my $cwd = getcwd();
    unless (chdir($folder)) {
        chdir($cwd);
        return;
    }
    return $cwd;
}

sub GetVariables () {
    # precondition: current folder is repo root

    # read parameters into hash
    my %vars = ();
    open(my $fh, '<', 'config/DocBookConfig.ent') or die("Can't open 'config/DocBookConfig.ent' for reading: $!\n");
    while (my $line = <$fh>) {
        if ($line =~ /^\s*<!ENTITY\s+(\S+)\s+"(\S+)">/) {
            $vars{$1} = $2;
        }
    }
    close($fh);

    # check variables' names
    my @validNames = (
        'ChangeLogDate',
        'ChangeLogRelease',
        'ChangeLogIssuer',
        'ChangeLogProduct_LSR',
        'CopyrightYear',
    );
    my %validNames = map { $_ => 1 } @validNames;
    for my $name (keys %vars) {
        unless ($validNames{$name}) {
            die("error: unknown parameter '$name'\n");
        }
    }
    return \%vars;
}

sub ReadFile ($) {
    my ($filename) = @_;
    open(my $fh, '<', $filename) or die("error: can't open '$filename' for reading: $!\n");
    local $/;
    my $content = <$fh>;
    close($fh);
    return $content;
}

sub WriteFile ($$) {
    my ($filename, $content) = @_;
    open(my $fh, '>', $filename) or die("error: can't open '$filename' for writing: $!\n");
    print $fh $content;
    close($fh) or die("error: can't close '$filename'\n");
}

sub FormatXML ($$) {
=comment
  There are different ways to format XML:
  * use specific module or function (i.e. XML::LibXML::PrettyPrint)
  * use XSL transformation

  I prefer xslt because
  * it can be used without this script
  * formatting style can be modified separately
=cut

    my ($xml, $prettyXmlPath) = @_;

    my $parser = new XML::LibXML;
    my $dom = $parser->load_xml(string  => $xml)
        or die("error: can't load xml from string: $!\n");

    my $xslt = XML::LibXSLT->new();
    my $style_doc = XML::LibXML->load_xml(location => $prettyXmlPath);
    my $stylesheet = $xslt->parse_stylesheet($style_doc);
    my $results = $stylesheet->transform($dom);
    return $stylesheet->output_as_chars($results);
}

sub CompareVersions ($$) {
    # this code is from http://cpansearch.perl.org/src/NEILB/Sort-Versions-1.60/lib/Sort/Versions.pm

    my @A = ($_[0] =~ /([-.]|\d+|[^-.\d]+)/g);
    my @B = ($_[1] =~ /([-.]|\d+|[^-.\d]+)/g);

    my ($A, $B);
    while (@A and @B) {
        $A = shift @A;
        $B = shift @B;
        if ($A eq '-' and $B eq '-') {
            next;
        } elsif ( $A eq '-' ) {
            return -1;
        } elsif ( $B eq '-') {
            return 1;
        } elsif ($A eq '.' and $B eq '.') {
            next;
        } elsif ( $A eq '.' ) {
            return -1;
        } elsif ( $B eq '.' ) {
            return 1;
        } elsif ($A =~ /^\d+$/ and $B =~ /^\d+$/) {
            if ($A =~ /^0/ || $B =~ /^0/) {
            return $A cmp $B if $A cmp $B;
            } else {
            return $A <=> $B if $A <=> $B;
            }
        } else {
            $A = uc $A;
            $B = uc $B;
            return $A cmp $B if $A cmp $B;
        }
    }
    @A <=> @B;
}

sub UpdateChangeLog {
    my %params = @_;

    # change folder
    print "chdir to $params{'path'}\n" if $params{'verbose'};
    my $previousFolder = ChdirHelper($params{'path'})
        or die("error: can't chdir to '$params{'path'}': $!\n");

    # get current version
    my $verLong = $params{'releaseVersion'};
    $verLong =~ m!^(\d+\.\d+)(.*)$! or die("error: unknown version format\n");
    my $verShort = $1;

    # load template (sometimes it isn't required)
    my $parser = new XML::LibXML;
    my ($dom, $sectionRelease, $sectionDefects, $sectionFeatures) =
        UpdateChangeLog_LoadTemplate($parser, 'releases/release_X.XX.X.xml', $verLong, $verShort, \%params);

    # use release information file if it exists, otherwise use template
    my $releaseFilename = "releases/release_$verShort.X.xml";
    if (-e $releaseFilename) {
        ($dom, $sectionRelease) = UpdateChangeLog_LoadRelease($parser, $sectionRelease, $releaseFilename, $verLong);
    }

    # append new features
    my @featureFiles = grep(!/feature0+\.xml/, <drafts/feature*.xml>);
    if (scalar(@featureFiles)) {
        UpdateChangeLog_AppendFeatures($parser, $sectionRelease, $sectionFeatures, \@featureFiles);
    }
    else {
        $sectionFeatures->unbindNode();
        undef $sectionFeatures;
    }

    # append new fixed defects
    my @defectFiles = grep(!/defect0+\.xml/, <drafts/defect*.xml>);
    if (scalar(@defectFiles)) {
        UpdateChangeLog_AppendDefects($parser, $sectionRelease, $sectionDefects, \@defectFiles);
    }
    else {
        $sectionDefects->unbindNode();
        undef $sectionDefects;
    }

    # if any new features or fixed defects exist
    if ($sectionDefects || $sectionFeatures) {
        # write new features and fixed defects into release information file
        WriteFile($releaseFilename, FormatXML($dom->toString, $params{'prettyXmlPath'}));

        # remove sources for new features and fixed defects (delete drafts)
        foreach my $file (@defectFiles, @featureFiles) {
            unlink($file) or warn("Could not unlink $file: $!");
        }

        # insert link to current release information file into changelog.xml if it doesn't exist yet
        UpdateChangeLog_UpdateChangeLog($parser, $releaseFilename, \%params);

        # insert current release information into revision_history.xml if it doesn't exist yet
        UpdateChangeLog_UpdateRevisionHistory($parser, $verLong, \%params);
    }

    # restore current folder to previous one
    ChdirHelper($previousFolder) or die("error: can't chdir to $previousFolder\n");
    return 1;
}

sub UpdateChangeLog_LoadTemplate {
    my ($parser, $filename, $verLong, $verShort, $params) = @_;

    my $dom = $parser->load_xml(location => $filename)
        or die("error: can't load '$filename': $!\n");

    # get defects section ...
    my ($sectionDefects) = $dom->findnodes('/db:section/db:section/db:section/db:title[text()="Fixed Defects"]/..')
        or die("error: can't find defects section in template\n");
    $sectionDefects->unbindNode();
    # ... without examples
    for my $node ($sectionDefects->getElementsByTagName('row')) {
        $node->unbindNode();
    }

    # get features section ...
    my ($sectionFeatures) = $dom->findnodes('/db:section/db:section/db:section/db:title[text()="New Features"]/..')
        or die("error: can't find features section in template\n");
    $sectionFeatures->unbindNode();
    # ... without examples
    for my $node ($sectionFeatures->getElementsByTagName('row')) {
        $node->unbindNode();
    }

    # update major release version
    my ($sectionRelease) = $dom->findnodes('/db:section/db:section/db:title[text()="Release X.XX.X"]/..')
        or die("error: can't find release section in template\n");

    my ($t) = $dom->findnodes("/db:section/db:title")
        or die("error: no /section/title node");
    $t->removeChildNodes();
    $t->appendText("Changelog For Release $verShort.X");
    undef $t;

    ($t) = $sectionRelease->findnodes("db:title")
        or die("error: no title node");
    $t->removeChildNodes();
    $t->appendText("Release $verLong");
    undef $t;

    return ($dom, $sectionRelease, $sectionDefects, $sectionFeatures);
}

sub UpdateChangeLog_LoadRelease {
    my ($parser, $sectionRelease, $releaseFilename, $verLong) = @_;

    my $dom = $parser->load_xml(location => $releaseFilename)
        or die("error: can't load '$releaseFilename': $!\n");

    # find all releases (inside major version)
    my @titleSections = $dom->findnodes("/db:section/db:section/db:title");
    my %titleSections = ();
    foreach my $title (@titleSections) {
        my ($number) = ($title->textContent() =~ /(\d+(\.\w+)*)/); # extract version
        $titleSections{$number} = $title->parentNode;
    }

    # is there already a section for current version?
    if (exists $titleSections{$verLong}) {
        # yes, replace section from template with section from release information file
        $sectionRelease = $titleSections{$verLong};
    }
    else {
        # no, append new section from template
        #$sectionRelease->unbindNode();
        $titleSections{$verLong} = $sectionRelease;
    }

    # sort sections by version (new section is inserted into the correct place)
    my ($sectionTitle) = $dom->findnodes("/db:section/db:title")
        or die("error: no /section/title node");
    my @versions = sort CompareVersions keys %titleSections;
    for my $node (map {$titleSections{$_}} @versions) {
        $node->unbindNode();
        # WORKAROUND: addSibling doesn't handle namespace correctly
        # $sectionTitle->addSibling($node);
        $sectionTitle->parentNode->insertAfter($node, $sectionTitle);
    }

    return ($dom, $sectionRelease);
}

sub UpdateChangeLog_AppendFeatures {
    my ($parser, $sectionRelease, $sectionFeatures, $featureFiles) = @_;

    # if there are new features and no section for them exists yet, then append such section
    my ($t) = $sectionRelease->findnodes('db:section/db:title[text()="New Features"]/..');
    unless ($t) {
        $sectionFeatures->unbindNode();
        $sectionRelease->appendChild($sectionFeatures);
    }
    else {
        $sectionFeatures = $t;
    }

    # append new features inside tbody
    my ($tbody) = $sectionFeatures->findnodes("db:informaltable/db:tgroup/db:tbody")
        or die("error: no informaltable/tgroup/tbody node");

    foreach my $file (@$featureFiles) {
        my $featureDom = $parser->load_xml(location => $file);

        # use entry1 tag as content of title tag
        my ($entry1) = $featureDom->findnodes("/db:section/db:title")
            or die("error: no section/title node");
        $entry1->unbindNode();
        $entry1->setNodeName('entry');

        # prepend "Feature " before number
        my $entry1Text = $entry1->textContent();
        $entry1->removeChildNodes();
        $entry1->appendText("Feature $entry1Text");

        # use all left tags as entry2 tag
        my $entry2 = XML::LibXML::Element->new('entry');
        my @childnodes = $featureDom->findnodes("/db:section")->shift->childNodes();
        foreach my $node (@childnodes) {
            $node->unbindNode();
            $entry2->appendChild($node);
        }

        my $row = XML::LibXML::Element->new('row');
        $row->appendChild($entry1);
        $row->appendChild($entry2);
        $tbody->insertBefore($row, $tbody->firstChild);

        undef $featureDom;
    }
}

sub UpdateChangeLog_AppendDefects {
    my ($parser, $sectionRelease, $sectionDefects, $defectFiles) = @_;

    # if there are fixed defects and no section for them exists yet, then append such section
    my ($t) = $sectionRelease->findnodes('db:section/db:title[text()="Fixed Defects"]/..');
    unless ($t) {
        $sectionDefects->unbindNode();
        $sectionRelease->appendChild($sectionDefects);
    }
    else {
        $sectionDefects = $t;
    }

    # append fixed defects inside tbody
    my ($tbody) = $sectionDefects->findnodes("db:informaltable/db:tgroup/db:tbody")
        or die("error: no informaltable/tgroup/tbody node");

    foreach my $file (@$defectFiles) {
        my $defectDom = $parser->load_xml(location => $file);

        # use entry1 tag as content of title tag
        my ($entry1) = $defectDom->findnodes("/db:section/db:title")
            or die("error: no section/title node");
        $entry1->unbindNode();
        $entry1->setNodeName('entry');

        # prepend "Defect " before number
        my $entry1Text = $entry1->textContent();
        $entry1->removeChildNodes();
        $entry1->appendText("Defect $entry1Text");

        # use all left tags as entry2 tag
        my $entry2 = XML::LibXML::Element->new('entry');
        my @childnodes = $defectDom->findnodes("/db:section")->shift->childNodes();
        foreach my $node (@childnodes) {
            $node->unbindNode();
            $entry2->appendChild($node);
        }

        my $row = XML::LibXML::Element->new('row');
        $row->appendChild($entry1);
        $row->appendChild($entry2);
        $tbody->insertBefore($row, $tbody->firstChild);

        undef $defectDom;
    }
}

sub UpdateChangeLog_UpdateChangeLog {
    my ($parser, $releaseFilename, $params) = @_;

    my $changelogFilename = 'changelog.xml';
    my $dom = $parser->load_xml(location => $changelogFilename)
        or die("error: can't load '$changelogFilename': $!\n");

    # if there is no section with current release version ...
    unless ($dom->findnodes("/db:section/xi:include[\@href='$releaseFilename']")) {
        # ... then append it
        my ($title) = $dom->findnodes("/db:section/db:title")
            or die("error: no section/title node");

        my $include = XML::LibXML::Element->new('xi:include');
        $include->setAttribute('href', $releaseFilename);
        $include->setAttribute('xpointer', 'element(/1)');
        $title->parentNode->insertAfter($include, $title);

        my $hardbreak = $dom->createProcessingInstruction('hard-pagebreak');
        $title->parentNode->insertAfter($hardbreak, $include);

        WriteFile($changelogFilename, FormatXML($dom->toString, $$params{'prettyXmlPath'}));
    }
}

sub UpdateChangeLog_UpdateRevisionHistory {
    my ($parser, $verLong, $params) = @_;

    my $revisionFilename = 'revision_history.xml';
    my $dom = $parser->load_xml(location => $revisionFilename)
        or die("error: can't load '$revisionFilename': $!\n");

    # delete section with current release version if it exists
    my ($row) = $dom->findnodes("/db:section/db:section/db:informaltable/db:tgroup/db:tbody/db:row/db:entry[text()=\"Release $verLong\"]/..");
    if ($row) {
        $row->unbindNode();
        undef $row;
    }

    # append information (without sorting)
    my ($tbody) = $dom->findnodes("/db:section/db:section/db:informaltable/db:tgroup/db:tbody")
        or die("error: no section/informaltable/tgroup/tbody node");
    $row = XML::LibXML::Element->new('row');
    $tbody->appendChild($row);

    my $entry1 = XML::LibXML::Element->new('entry');
    $entry1->appendText($$params{'releaseDate'});
    $row->appendChild($entry1);

    my $entry2 = XML::LibXML::Element->new('entry');
    $entry2->appendText("Release $verLong");
    $row->appendChild($entry2);

    WriteFile($revisionFilename, FormatXML($dom->toString, $$params{'prettyXmlPath'}));
}

my @changeLogFolders = (
    'doc/changelog'
);

my $script = basename($0);
my $scriptDir = abs_path(dirname($0));

# parse parameters
my $help        = undef;
my $verbose     = undef;
my $repoPath = "$scriptDir/../.."; # assume that the script is in support/UpdateChangeLogs

GetOptions(
    "help"           => \$help,
    "verbose"        => \$verbose,
    "repo-path=s" => \$repoPath,
) or die("error in command line parameters.\nUse '$script --help' for help\n");

# show help and exit
if ($help) {
    open(my $fh, '<', $0) or die("error: could not open '$0' for reading: $!\n");
    my $usage;
    {
        local $/;
        my $source = <$fh>;
        close($fh);
        ($usage) = $source =~ m!^=head1 USAGE(.+?)=head1!ms;
    }
    print $usage;
    exit(0);
}

unless (ChdirHelper($repoPath)) {
    exit(1);
}

my $variablesRef = GetVariables();
my %params = (
    verbose          => $verbose,
    prettyXmlPath    => "$scriptDir/Indent.xsl",
    releaseDate      => $$variablesRef{'ChangeLogDate'},
    releaseVersion   => $$variablesRef{'ChangeLogRelease'},
);

foreach my $f (@changeLogFolders) {
    UpdateChangeLog(%params, 'path' => $f);
}
