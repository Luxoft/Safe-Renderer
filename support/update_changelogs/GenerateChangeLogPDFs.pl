#!/usr/bin/perl

=head1 NAME
  GenerateChangeLogPDFs.pl

  Generate PDF files and put them in root folder of repository for
  * changelog\main.xml

=head1 USAGE
  perl GenerateChangeLogPDFs.pl

=cut

BEGIN {
    if ($^O eq 'msys') {
        die <<'EOF';

You are running this script using Perl from Git installation.
Batch files can't be executed correctly from msys ("git") environment.
Please install Strawberry Perl as described on
https://adc.luxoft.com/confluence/display/POPULUS/Software#Software-perl

EOF
    }
}

use strict;
use warnings;
use File::Basename;
use File::Spec;
use Cwd qw(getcwd abs_path);

sub GetVariables () {
    # precondition: current folder is script folder

    # read parameters into hash
    my %vars = ();
    open(my $fh, '<', '../../config/DocBookConfig.ent') or die("Can't open 'config/DocBookConfig.ent' for reading: $!\n");
    while (my $line = <$fh>) {
        if ($line =~ /^\s*<!ENTITY\s+(\S+)\s+"(\S+)">/) {
            $vars{$1} = $2;
        }
    }
    close($fh);

    # check variables names
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

sub EscapePath ($) {
    my $path = shift;
    $path = '"' . $path . '"'
        if $path =~ m/ /;
    return $path;
}

sub RunCmd {
    system(@_) == 0
        or die "system '" . join(" ", @_) . "' failed: $?\n";
}

my $outputDir = getcwd();
my $scriptDir = abs_path($0);
$scriptDir =~ s!\\!/!g;
$scriptDir = dirname($scriptDir);

unless (chdir($scriptDir)) {
    print STDERR "error: can't change folder to $scriptDir\n";
    exit(1);
}

my $vars = GetVariables();
my %files = (
    '..\doc\changelog\main.xml'    => "LXFT.LSR.SCL.$$vars{'ChangeLogRelease'}-(Luxoft Safe Renderer Changelog).pdf",
);

print "Converting main changelog XML into PDF...\n";
while (my ($docbook, $pdf) = each(%files)) {
    print "\n\nProcessing $docbook...\n";
    RunCmd('..\DocBook\ConvertChangeLogToPDF.bat', EscapePath("..\\$docbook"), EscapePath("$outputDir\\$pdf"));
}

chdir('..\..');
print "\n\nDone! Resulting files are in " . $outputDir . "\n";
exit(0)
