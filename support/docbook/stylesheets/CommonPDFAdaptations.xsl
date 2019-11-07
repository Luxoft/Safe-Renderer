<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE stylesheet [
<!ENTITY % myents SYSTEM "../../../config/DocBookConfig.ent">
%myents;
]>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:fo="http://www.w3.org/1999/XSL/Format" version="1.0">
  <!-- The local path to Norm Walsh's DocBook FO stylesheets -->
  <xsl:import href="../../../DK_Win/tools/docbook-xsl/1.79.1/fo/docbook.xsl"/>

  <!-- ***************  Additional  *********************  -->
  <xsl:param name="paper.type">A4</xsl:param>
  <xsl:param name="fop1.extensions" select="1"/>
  <xsl:param name="header.image.filename">file:///../images/LUXOFT_DXC_logo_rgb_blue_2019.png</xsl:param>
  <!-- Do not indent body text relative to section titles -->
  <xsl:param name="body.start.indent">0pt</xsl:param>

  <!-- Hyphenation is turned on everywhere except for section titles -->
  <xsl:attribute-set name="section.title.level1.properties">
    <xsl:attribute name="hyphenate">false</xsl:attribute>
  </xsl:attribute-set>
  <xsl:attribute-set name="section.title.level2.properties">
    <xsl:attribute name="hyphenate">false</xsl:attribute>
  </xsl:attribute-set>
  <xsl:attribute-set name="section.title.level3.properties">
    <xsl:attribute name="hyphenate">false</xsl:attribute>
  </xsl:attribute-set>
  <xsl:attribute-set name="section.title.level4.properties">
    <xsl:attribute name="hyphenate">false</xsl:attribute>
  </xsl:attribute-set>

  <!-- ***************************************************  -->
  <!-- ***************  Admonitions  *********************  -->
  <!-- ***************************************************  -->
  <!-- If true (non-zero), admonitions are presented in an alternate style that uses a graphic. Default graphics are provided in the distribution. -->
  <xsl:param name="admon.graphics" select="1"/>
  <!-- Sets the extension to use on admonition graphics. -->
  <xsl:param name="admon.graphics.extension">.svg</xsl:param>
  <!-- Sets the path to the directory containing the admonition graphics (caution.png, important.png, etc.). This location is normally relative to the output directory. -->
  <xsl:param name="admon.graphics.path">file:///../../../DK_Win/tools/docbook-xsl/1.79.1/images/</xsl:param>
  <!-- If true (non-zero), admonitions are presented with a generated text label such as Note or Warning in the appropriate language. If zero, such labels are turned off, but any title child of the admonition element is still output. The default value is 1. -->
  <xsl:param name="admon.textlabel" select="1"/>
  <!-- Set the size for admonition graphics, default is 36pt -->
  <xsl:template match="*" mode="admon.graphic.width">
    <xsl:param name="node" select="."/>
    <xsl:text>24pt</xsl:text>
  </xsl:template>
  <!-- For graphical admonitions, reduce the gap between graphic and text label -->
  <xsl:template name="graphical.admonition">
    <xsl:variable name="id">
      <xsl:call-template name="object.id"/>
    </xsl:variable>
    <xsl:variable name="graphic.width">
      <xsl:apply-templates select="." mode="admon.graphic.width"/>
    </xsl:variable>
    <fo:block id="{$id}"
              xsl:use-attribute-sets="graphical.admonition.properties">
      <fo:list-block provisional-distance-between-starts="{$graphic.width} + 9pt"
                     provisional-label-separation="9pt">
        <fo:list-item>
          <fo:list-item-label end-indent="label-end()">
            <fo:block>
              <fo:external-graphic width="auto" height="auto"
                                   content-width="{$graphic.width}" >
                <xsl:attribute name="src">
                  <xsl:call-template name="admon.graphic"/>
                </xsl:attribute>
              </fo:external-graphic>
            </fo:block>
          </fo:list-item-label>
          <fo:list-item-body start-indent="body-start()">
            <xsl:if test="$admon.textlabel != 0 or title or info/title">
              <fo:block xsl:use-attribute-sets="admonition.title.properties">
                <xsl:apply-templates select="." mode="object.title.markup">
                  <xsl:with-param name="allow-anchors" select="1"/>
                </xsl:apply-templates>
              </fo:block>
            </xsl:if>
            <fo:block xsl:use-attribute-sets="admonition.properties">
              <xsl:apply-templates/>
            </fo:block>
          </fo:list-item-body>
        </fo:list-item>
      </fo:list-block>
    </fo:block>
  </xsl:template>
  <!-- Make admonition label text font smaller (12pt instead of 14), and even smaller in tables and informaltables -->
  <xsl:attribute-set name="admonition.title.properties">
    <xsl:attribute name="font-size">
      <xsl:variable name="lsr.admonition.font.size" select="12"/>
      <xsl:choose>
        <xsl:when test="(ancestor::informaltable | ancestor::table)">
          <xsl:value-of select="$lsr.admonition.font.size * $met.table.head.font.size"/>
        </xsl:when>
        <xsl:otherwise>
          <xsl:value-of select="$lsr.admonition.font.size"/>
        </xsl:otherwise>
      </xsl:choose>
      <xsl:text>pt</xsl:text>
    </xsl:attribute>
    <xsl:attribute name="font-weight">bold</xsl:attribute>
    <xsl:attribute name="hyphenate">false</xsl:attribute>
    <xsl:attribute name="keep-with-next.within-column">always</xsl:attribute>
  </xsl:attribute-set>

  <!-- ***************  Automatic labelling  *********************  -->
  <!-- ***************************************************  -->
  <!-- If true (non-zero), unlabeled sections will be enumerated. -->
  <xsl:param name="section.autolabel" select="1"/>
  <!-- If non-zero, section labels are prefixed with the label of the component that contains them.  -->
  <xsl:param name="section.label.includes.component.label" select="1"/>

  <!-- ***************  Bibliography  *********************  -->
  <!-- ***************************************************  -->

  <!-- ***************  Callouts  *********************  -->
  <!-- ***************************************************  -->
  <!-- If non-zero, callouts are presented with graphics (e.g., reverse-video circled numbers instead of "(1)", "(2)", etc.). Default graphics are provided in the distribution. -->
  <xsl:param name="callout.graphics" select="1"/>
  <!-- Sets the path to the directory holding the callout graphics. This location is normally relative to the output directory. Always terminate the directory with / since the graphic file is appended to this string, hence needs the separator. -->
  <xsl:param name="callout.graphics.path">file:///../../../DK_Win/tools/docbook-xsl/1.79.1/images/callouts/</xsl:param>
  <!-- Specifies the size of the callout marker icons. The default size is 7 points. -->
  <xsl:param name="callout.icon.size">7pt</xsl:param>

  <!-- ***************  Colors  *********************  -->
  <!-- ***************************************************  -->
  <!-- The attribute "role" of the <phrase> element allows defining inline text color and background color:
         - fgcolor=#FAFAC0; - to define foreground color.
         - bgcolor=#C70039; - to define background color.
       Examples:
         <phrase role=”fgcolor:red;bgcolor:yellow;”>red text on yellow background</phrase>
         <phrase role=”fgcolor:#F72306;”>red text on default (white) background</phrase>
         <phrase role=”bgcolor:#F5F904;”>default-color (black) text on yellow background</phrase>
       Color may be specified with standard names (red, blue, etc.) or in HEX notation, like #900C3F.
       Any other value will not corrupt the FO output, simply won't apply any formatting.  -->
  <xsl:template match="phrase">
    <xsl:choose>
      <xsl:when test="@role">
        <xsl:choose>
          <xsl:when test="contains(@role, 'fgcolor:') and contains(@role, 'bgcolor:')">
            <xsl:variable name="fg" select="substring-before(substring-after(@role, 'fgcolor:'), ';')" />
            <xsl:variable name="bg" select="substring-before(substring-after(@role, 'bgcolor:'), ';')" />
            <fo:inline>
              <xsl:attribute name="color">
                <xsl:value-of select="$fg" />
              </xsl:attribute>
              <xsl:attribute name="background-color">
                <xsl:value-of select="$bg" />
              </xsl:attribute>
              <xsl:call-template name="inline.charseq"/>
            </fo:inline>
          </xsl:when>
          <xsl:when test="contains(@role, 'fgcolor:') and not(contains(@role, 'bgcolor:'))">
            <xsl:variable name="fg" select="substring-before(substring-after(@role, 'fgcolor:'), ';')" />
            <fo:inline>
              <xsl:attribute name="color">
                <xsl:value-of select="$fg" />
              </xsl:attribute>
              <xsl:call-template name="inline.charseq"/>
            </fo:inline>
          </xsl:when>
          <xsl:when test="contains(@role, 'bgcolor:') and not(contains(@role, 'fgcolor:'))">
            <xsl:variable name="bg" select="substring-before(substring-after(@role, 'bgcolor:'), ';')" />
            <fo:inline>
              <xsl:attribute name="background-color">
                <xsl:value-of select="$bg" />
              </xsl:attribute>
              <xsl:call-template name="inline.charseq"/>
            </fo:inline>
          </xsl:when>
          <xsl:otherwise>
            <xsl:call-template name="inline.charseq"/>
          </xsl:otherwise>
        </xsl:choose>
      </xsl:when>
      <xsl:otherwise>
        <xsl:call-template name="inline.charseq"/>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>

  <!-- ***************  Cross References  *********************  -->
  <!-- ***************************************************  -->

  <!-- ***************  EBNF  *********************  -->
  <!-- ***************************************************  -->

  <!-- ***************  Font Families  *********************  -->
  <!-- ***************************************************  -->
  <xsl:param name="body.font.family">sans-serif</xsl:param>

  <!-- ***************  Glossary  *********************  -->
  <!-- ***************************************************  -->
  <xsl:param name="glossary.sort">1</xsl:param>

  <!-- ***************  Graphics  *********************  -->
  <!-- ***************************************************  -->
  <!-- When indentation is removed, images become left-aligned. This is to center them -->
  <xsl:attribute-set name="informalfigure.properties">
    <xsl:attribute name="text-align">center</xsl:attribute>
  </xsl:attribute-set>
  <xsl:attribute-set name="figure.properties">
    <xsl:attribute name="text-align">center</xsl:attribute>
  </xsl:attribute-set>

  <!-- ***************  Linking  *********************  -->
  <!-- ***************************************************  -->
  <!-- Internal links: default color, italic, underlined -->
  <!-- External links: blue color, non-italic, underlined -->
  <xsl:attribute-set name="xref.properties">
    <xsl:attribute name="text-decoration">underline</xsl:attribute>
    <xsl:attribute name="color">blue</xsl:attribute>
    <xsl:attribute name="font-style">
      <xsl:choose>
        <xsl:when test="self::ulink">inherit</xsl:when>
        <xsl:otherwise>italic</xsl:otherwise>
      </xsl:choose>
    </xsl:attribute>
  </xsl:attribute-set>

  <!-- ***************  Lists  *********************  -->
  <!-- ***************************************************  -->
  <!-- Indent lists relative to parent body text -->
  <!-- Indentation will be smaller inside tables and informaltables -->
  <xsl:attribute-set name="list.block.properties">
    <xsl:attribute name="margin-left">
      <xsl:choose>
        <xsl:when test="ancestor::table | ancestor::informaltable">8pt</xsl:when>
        <xsl:when test="count(ancestor::listitem)">inherit</xsl:when>
        <xsl:otherwise>20pt</xsl:otherwise>
      </xsl:choose>
    </xsl:attribute>
  </xsl:attribute-set>

  <!-- ***************  Localization  *********************  -->
  <!-- ***************************************************  -->

  <!-- ***************  Meta/*Info  *********************  -->
  <!-- ***************************************************  -->

  <!-- ***************  Miscellaneous  *********************  -->
  <!-- ***************************************************  -->
  <xsl:param name="ulink.show" select="0"/>
  <xsl:param name="shade.verbatim" select="1"/>
  <xsl:attribute-set name="shade.verbatim.style">
    <xsl:attribute name="background-color">#E0E0E0</xsl:attribute>
    <xsl:attribute name="border-width">0.5pt</xsl:attribute>
    <xsl:attribute name="border-style">solid</xsl:attribute>
    <xsl:attribute name="border-color">#575757</xsl:attribute>
    <xsl:attribute name="padding">3pt</xsl:attribute>
  </xsl:attribute-set>
  <xsl:param name="show.comments" select="0"/>
  <!-- ***************  Pagination and General Styles  *********************  -->
  <xsl:param name="header.column.widths">6 0 1</xsl:param>
  <xsl:param name="footer.column.widths">3 1 3</xsl:param>
  <xsl:param name="marker.section.level">1</xsl:param>
  <!-- ********  Colored blocks for equations and examples  **************  -->
  <xsl:attribute-set name="equation.properties">
    <xsl:attribute name="border-style">none</xsl:attribute>
    <xsl:attribute name="padding">0.5em</xsl:attribute>
    <xsl:attribute name="background-color">#F0F3FA</xsl:attribute>
  </xsl:attribute-set>
  <xsl:attribute-set name="informalequation.properties" use-attribute-sets="equation.properties"/>
  <xsl:attribute-set name="example.properties">
    <xsl:attribute name="border-style">none</xsl:attribute>
    <xsl:attribute name="padding">0.5em</xsl:attribute>
    <xsl:attribute name="background-color">#F0F3FA</xsl:attribute>
  </xsl:attribute-set>
  <xsl:attribute-set name="informalexample.properties" use-attribute-sets="example.properties"/>
  <!-- ********  Prevent body text from overlapping footer ********  -->
  <xsl:param name="body.margin.bottom">0.8in</xsl:param>
  <!-- ********  Make blockquote margins smaller ********  -->
  <xsl:template match="blockquote">
    <xsl:variable name="keep.together">
      <xsl:call-template name="pi.dbfo_keep-together"/>
    </xsl:variable>
    <fo:block xsl:use-attribute-sets="blockquote.properties">
      <xsl:attribute name="margin-{$direction.align.start}">0.1in</xsl:attribute>
      <xsl:attribute name="margin-{$direction.align.end}">0.1in</xsl:attribute>
      <xsl:attribute name="background-color">#F0F3FA</xsl:attribute>
      <xsl:if test="$keep.together != ''">
        <xsl:attribute name="keep-together.within-column"><xsl:value-of
                       select="$keep.together"/></xsl:attribute>
      </xsl:if>
      <xsl:call-template name="anchor"/>
      <fo:block>
        <xsl:if test="title|info/title">
          <fo:block xsl:use-attribute-sets="formal.title.properties">
            <xsl:apply-templates select="." mode="object.title.markup"/>
          </fo:block>
        </xsl:if>
        <xsl:apply-templates select="*[local-name(.) != 'title'
                                     and local-name(.) != 'attribution']"/>
      </fo:block>
      <xsl:if test="attribution">
        <fo:block text-align="right">
          <!-- mdash -->
          <xsl:text>&#x2014;</xsl:text>
          <xsl:apply-templates select="attribution"/>
        </fo:block>
      </xsl:if>
    </fo:block>
  </xsl:template>

  <!-- ***************  Prepress  *********************  -->
  <!-- ***************************************************  -->

  <!-- ***************  Processor Extensions  *********************  -->
  <!-- ***************************************************  -->

  <!-- ***************  Profiling  *********************  -->
  <!-- ***************************************************  -->

  <!-- ***************  Property Sets  *********************  -->
  <!-- ***************************************************  -->
  <xsl:attribute-set name="monospace.verbatim.properties">
    <xsl:attribute name="font-family">Courier</xsl:attribute>
    <!-- Check if we are in an informaltable or table and resize the font accordingly -->
    <xsl:attribute name="font-size">
      <xsl:variable name="lsr.monospace.font.size" select="8.4"/>
      <xsl:choose>
        <xsl:when test="ancestor::*[name() = name(//informaltable)] or ancestor::*[name() = name(//table)]">
          <xsl:value-of select="$lsr.monospace.font.size * $met.table.font.size"/>
        </xsl:when>
        <xsl:otherwise>
          <xsl:value-of select="$lsr.monospace.font.size"/>
        </xsl:otherwise>
      </xsl:choose>
      <xsl:text>pt</xsl:text>
    </xsl:attribute>
    <xsl:attribute name="keep-together.within-column">auto</xsl:attribute>
    <xsl:attribute name="wrap-option">wrap</xsl:attribute>
    <xsl:attribute name="hyphenation-character">\</xsl:attribute>
  </xsl:attribute-set>

  <!-- ***************  QAndASet  *********************  -->
  <!-- ***************************************************  -->

  <!-- ***************  Reference Pages  *********************  -->
  <!-- ***************************************************  -->

  <!-- ***************  Revision History  *********************  -->
  <!-- ***************************************************  -->
  <xsl:attribute-set name="revhistory.title.properties">
    <xsl:attribute name="font-size">12pt</xsl:attribute>
    <xsl:attribute name="font-weight">bold</xsl:attribute>
    <xsl:attribute name="text-align">center</xsl:attribute>
  </xsl:attribute-set>
  <xsl:attribute-set name="revhistory.table.properties">
    <xsl:attribute name="border">0.5pt solid black</xsl:attribute>
    <xsl:attribute name="background-color">#EEEEEE</xsl:attribute>
    <xsl:attribute name="width">50%</xsl:attribute>
  </xsl:attribute-set>
  <xsl:attribute-set name="revhistory.table.cell.properties">
    <xsl:attribute name="border">0.5pt solid black</xsl:attribute>
    <xsl:attribute name="font-size">9pt</xsl:attribute>
    <xsl:attribute name="padding">4pt</xsl:attribute>
  </xsl:attribute-set>

  <!-- Template for Revision History table -->
  <xsl:template match="revhistory" mode="titlepage.mode">
    <xsl:variable name="explicit.table.width">
      <xsl:call-template name="pi.dbfo_table-width"/>
    </xsl:variable>
    <xsl:variable name="table.width">
      <xsl:choose>
        <xsl:when test="$explicit.table.width != ''">
          <xsl:value-of select="$explicit.table.width"/>
        </xsl:when>
        <xsl:when test="$default.table.width = ''">
          <xsl:text>100%</xsl:text>
        </xsl:when>
        <xsl:otherwise>
          <xsl:value-of select="$default.table.width"/>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:variable>

    <fo:table table-layout="fixed" width="{$table.width}" xsl:use-attribute-sets="revhistory.table.properties">
      <fo:table-column column-number="1" column-width="proportional-column-width(1)"/>
      <fo:table-column column-number="2" column-width="proportional-column-width(1)"/>
      <fo:table-column column-number="3" column-width="proportional-column-width(1)"/>
      <fo:table-body start-indent="0pt" end-indent="0pt">
        <fo:table-row>
          <fo:table-cell number-columns-spanned="3" xsl:use-attribute-sets="revhistory.table.cell.properties"
              background-color="#383838" color="#FFFFFF">
            <fo:block xsl:use-attribute-sets="revhistory.title.properties">
              <xsl:choose>
              <xsl:when test="title|info/title">
                <xsl:apply-templates select="title|info/title" mode="titlepage.mode"/>
              </xsl:when>
              <xsl:otherwise>
              <xsl:call-template name="gentext">
                <xsl:with-param name="key" select="'RevHistory'"/>
              </xsl:call-template>
              </xsl:otherwise>
            </xsl:choose>
          </fo:block>
          </fo:table-cell>
        </fo:table-row>
        <xsl:apply-templates select="*[not(self::title)]" mode="titlepage.mode"/>
      </fo:table-body>
    </fo:table>
  </xsl:template>

  <!-- Template for a single revision inside the Revision History table -->
  <xsl:template match="revhistory/revision" mode="titlepage.mode">
    <xsl:variable name="revnumber" select="revnumber"/>
    <xsl:variable name="revdate"   select="date"/>
    <xsl:variable name="revauthor" select="authorinitials|author"/>
    <xsl:variable name="revremark" select="revremark|revdescription"/>
    <fo:table-row>
      <fo:table-cell xsl:use-attribute-sets="revhistory.table.cell.properties">
        <fo:block>
          <xsl:if test="$revnumber">
            <xsl:call-template name="gentext">
              <xsl:with-param name="key" select="'Revision'"/>
            </xsl:call-template>
            <xsl:call-template name="gentext.space"/>
            <xsl:apply-templates select="$revnumber[1]" mode="titlepage.mode"/>
          </xsl:if>
        </fo:block>
      </fo:table-cell>
      <fo:table-cell xsl:use-attribute-sets="revhistory.table.cell.properties">
        <fo:block>
          <xsl:apply-templates select="$revdate[1]" mode="titlepage.mode"/>
        </fo:block>
      </fo:table-cell>
      <fo:table-cell xsl:use-attribute-sets="revhistory.table.cell.properties">
        <fo:block>
          <xsl:for-each select="$revauthor">
            <xsl:apply-templates select="." mode="titlepage.mode"/>
            <xsl:if test="position() != last()">
              <xsl:text>, </xsl:text>
            </xsl:if>
          </xsl:for-each>
        </fo:block>
      </fo:table-cell>
    </fo:table-row>
    <xsl:if test="$revremark">
      <fo:table-row>
        <fo:table-cell number-columns-spanned="3" xsl:use-attribute-sets="revhistory.table.cell.properties"
            background-color="#FFFFFF" text-align="left">
          <fo:block>
            <xsl:apply-templates select="$revremark[1]" mode="titlepage.mode"/>
          </fo:block>
        </fo:table-cell>
      </fo:table-row>
    </xsl:if>
  </xsl:template>

  <!-- ***************  Stylesheet Extensions  *********************  -->
  <!-- ***************************************************  -->

  <!-- ***************  Tables  *********************  -->
  <!-- ***************************************************  -->
  <!-- font size for table -->
  <xsl:param name="met.table.font.size">0.8</xsl:param>
  <xsl:param name="met.table.head.font.size">0.9</xsl:param>
  <!-- Set table body font size and alignment -->
  <xsl:attribute-set name="table.properties">
    <xsl:attribute name="keep-together.within-column">auto</xsl:attribute>
    <xsl:attribute name="font-size">
      <xsl:value-of select="$body.font.master * $met.table.font.size"/>
      <xsl:text>pt</xsl:text>
    </xsl:attribute>
  </xsl:attribute-set>
  <!-- Set table header font size -->
  <xsl:template name="table.row.properties">
    <xsl:if test="ancestor::thead">
      <xsl:attribute name="font-weight">bold</xsl:attribute>
      <xsl:attribute name="color">#FFFFFF</xsl:attribute>
      <!-- White -->
      <xsl:attribute name="background-color">#585858</xsl:attribute>
      <!-- Black -->
      <xsl:attribute name="font-size">
        <xsl:value-of select="$body.font.master * $met.table.head.font.size"/>
        <xsl:text>pt</xsl:text>
      </xsl:attribute>
    </xsl:if>
    <!-- Fix for the default stylesheet to allow adding colors to the whole table row -->
    <xsl:variable name="bgcolor">
      <xsl:call-template name="pi.dbfo_bgcolor">
        <xsl:with-param name="node" select="ancestor-or-self::row"/>
      </xsl:call-template>
    </xsl:variable>
    <xsl:if test="$bgcolor != ''">
      <xsl:attribute name="background-color">
        <xsl:value-of select="$bgcolor"/>
      </xsl:attribute>
    </xsl:if>
  </xsl:template>
  <!-- For informal tables use formal table style -->
  <xsl:attribute-set name="informaltable.properties" use-attribute-sets="table.properties"/>
  <!-- cell padding for tables -->
  <xsl:attribute-set name="table.cell.padding">
    <xsl:attribute name="padding-left">4pt</xsl:attribute>
    <xsl:attribute name="padding-right">4pt</xsl:attribute>
    <xsl:attribute name="padding-top">2pt</xsl:attribute>
    <xsl:attribute name="padding-bottom">2pt</xsl:attribute>
  </xsl:attribute-set>
  <!-- Make titles for formal elements smaller if they are nested inside a table or informaltable -->
  <xsl:attribute-set name="formal.title.properties" use-attribute-sets="normal.para.spacing">
    <xsl:attribute name="font-weight">bold</xsl:attribute>
    <xsl:attribute name="font-size">
      <xsl:choose>
        <xsl:when test="ancestor::table | ancestor::informaltable">
          <xsl:value-of select="$body.font.master"/>
          <xsl:text>pt</xsl:text>
        </xsl:when>
        <xsl:otherwise>
          <xsl:value-of select="$body.font.master * 1.2"/>
          <xsl:text>pt</xsl:text>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:attribute>
    <xsl:attribute name="hyphenate">false</xsl:attribute>
    <xsl:attribute name="space-after.minimum">0.4em</xsl:attribute>
    <xsl:attribute name="space-after.optimum">0.6em</xsl:attribute>
    <xsl:attribute name="space-after.maximum">0.8em</xsl:attribute>
  </xsl:attribute-set>

  <!-- ***************  ToC/LoT/Index Generation  *********************  -->
  <!-- ***************************************************  -->
  <!-- This parameter has a structured value. It is a table of space-delimited path/value pairs. Each path identifies some element in the source document using a restricted subset of XPath (only the implicit child axis, no wildcards, no predicates). Paths can be either relative or absolute. When processing a particular element, the stylesheets consult this table to determine if a ToC (or LoT(s)) should be generated. For example, consider the entry: "book toc,figure" This indicates that whenever a book is formatted, a Table Of Contents and a List of Figures should be generated. Similarly, "/chapter toc" indicates that whenever a document that has a root of chapter is formatted, a Table of Contents should be generated. The entry chapter would match all chapters, but /chapter matches only chapter document elements. Generally, the longest match wins. So, for example, if you want to distinguish articles in books from articles in parts, you could use these two entries: "book/article toc,figure" and "part/article toc" Note that an article in a part can never match a book/article, so if you want nothing to be generated for articles in parts, you can simply leave that rule out. If you want to leave the rule in, to make it explicit that you're turning something off, use the value "nop". For example, the following entry disables ToCs and LoTs for articles: "article nop" Do not simply leave the word "article" in the file without a matching value. That'd be just begging the silly little path/value parser to get confused. Section ToCs are further controlled by the generate.section.toc.level parameter. For a given section level to have a ToC, it must have both an entry in generate.toc and be within the range enabled by generate.section.toc.level. -->
  <xsl:param name="toc.section.depth">4</xsl:param>
  <xsl:param name="generate.toc">
  appendix          toc,title
  article/appendix  nop
  article           toc,title
  book              toc,title
  chapter           nop
  part              toc,title
  preface           toc,title
  reference         toc,title
  sect1             toc
  sect2             toc
  sect3             toc
  sect4             toc
  sect5             toc
  section           toc
  set               toc,title
  </xsl:param>
  <!-- Using this role will exclude sections from TOC -->
  <xsl:template match="section[@role = 'NotInToc']"  mode="toc" />

  <!-- ***************  XSLT Processing  *********************  -->
  <!-- ***************************************************  -->
  <!-- allows to move TOC to a separate page, used in ArticleTitlepage.xml -->
  <xsl:template name="component.toc.separator">
    <fo:block break-after="page"/>
  </xsl:template>
  <!-- allows to add hard page breaks as processing instructions in docbook xml -->
  <xsl:template match="processing-instruction('hard-pagebreak')">
    <fo:block break-after="page"/>
  </xsl:template>
  <xsl:template match="processing-instruction('linebreak')">
    <fo:block/>
  </xsl:template>

  <!-- This is required to avoid errors with special symbol (like sum symbol) visualization -->
  <xsl:template match="symbol[@role = 'symbolfont']">
    <fo:inline font-family="Arial">
      <xsl:call-template name="inline.charseq"/>
    </fo:inline>
  </xsl:template>

  <!-- This formats appendices like 'Appendix 1. Title' for articles -->
  <xsl:param name="local.l10n.xml" select="document('')"/>
  <l:i18n xmlns:l="http://docbook.sourceforge.net/xmlns/l10n/1.0">
    <l:l10n language="en">
      <l:context name="title-numbered">
        <l:template name="article/appendix" text="Appendix %n.&#160;%t"/>
      </l:context>
      <l:context name="xref">
        <l:template name="article/appendix" text="Appendix %n.&#160;%t"/>
      </l:context>
      <l:context name="xref-number">
        <l:template name="article/appendix" text="Appendix %n.&#160;%t"/>
      </l:context>
      <l:context name="xref-number-and-title">
        <l:template name="article/appendix" text="Appendix %n.&#160;%t"/>
      </l:context>
    </l:l10n>
  </l:i18n>

  <!-- This adds the word Appendix to the appendix title in TOC -->
  <xsl:template name="toc.line">
    <xsl:param name="toc-context" select="NOTANODE"/>

    <xsl:variable name="id">
      <xsl:call-template name="object.id"/>
    </xsl:variable>

    <xsl:variable name="label">
      <xsl:choose>
        <xsl:when test="self::appendix">
          <xsl:call-template name="gentext">
            <xsl:with-param name="key">appendix</xsl:with-param>
          </xsl:call-template>
          <xsl:text> </xsl:text>
          <xsl:apply-templates select="." mode="label.markup"/>
        </xsl:when>
        <xsl:otherwise>
          <xsl:apply-templates select="." mode="label.markup"/>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:variable>

    <fo:block xsl:use-attribute-sets="toc.line.properties">
      <fo:inline keep-with-next.within-line="always">
        <fo:basic-link internal-destination="{$id}">
          <xsl:if test="$label != ''">
            <xsl:copy-of select="$label"/>
            <xsl:value-of select="$autotoc.label.separator"/>
          </xsl:if>
          <xsl:apply-templates select="." mode="titleabbrev.markup"/>
        </fo:basic-link>
      </fo:inline>
      <fo:inline keep-together.within-line="always">
        <xsl:text> </xsl:text>
          <fo:leader leader-pattern="dots"
                     leader-pattern-width="3pt"
                     leader-alignment="reference-area"
                     keep-with-next.within-line="always"/>
          <xsl:text> </xsl:text>
          <fo:basic-link internal-destination="{$id}">
            <fo:page-number-citation ref-id="{$id}"/>
          </fo:basic-link>
      </fo:inline>
    </fo:block>
  </xsl:template>

  <!-- ***************  Header and footer  *********************  -->
  <!-- Customizing the footer rule line -->
  <xsl:template name="foot.sep.rule">
    <xsl:param name="pageclass"/>
    <xsl:param name="sequence"/>
    <xsl:param name="gentext-key"/>

    <xsl:if test="$footer.rule != 0">
      <xsl:choose>
        <xsl:when test="$pageclass = 'titlepage'">
          <!-- do not show footer separator on title page -->
        </xsl:when>
        <xsl:otherwise>
          <xsl:attribute name="border-top-width">0.5pt</xsl:attribute>
          <xsl:attribute name="border-top-style">solid</xsl:attribute>
          <xsl:attribute name="border-top-color">#383838</xsl:attribute>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:if>
  </xsl:template>

  <!-- Customizing the header rule line -->
  <xsl:template name="head.sep.rule">
    <xsl:param name="pageclass"/>
    <xsl:param name="sequence"/>
    <xsl:param name="gentext-key"/>

    <xsl:if test="$header.rule != 0">
      <xsl:choose>
        <xsl:when test="$pageclass = 'titlepage'">
          <!-- do not show header separator on title page -->
        </xsl:when>
        <xsl:otherwise>
          <xsl:attribute name="border-bottom-width">0.5pt</xsl:attribute>
          <xsl:attribute name="border-bottom-style">solid</xsl:attribute>
          <xsl:attribute name="border-bottom-color">#383838</xsl:attribute>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:if>
  </xsl:template>

  <!-- Header properties -->
  <!-- Header content properties -->
  <xsl:attribute-set name="header.content.properties">
    <xsl:attribute name="font-size">8pt</xsl:attribute>
  </xsl:attribute-set>
  <!-- Header content itself -->
  <xsl:template name="header.content">
    <xsl:param name="pageclass" select="''"/>
    <xsl:param name="sequence" select="''"/>
    <xsl:param name="position" select="''"/>
    <xsl:param name="gentext-key" select="''"/>
    <fo:block>
      <xsl:choose>
        <xsl:when test="$sequence = 'blank' or $pageclass = 'lot'">
        </xsl:when>
        <xsl:when test="$position = 'left'">
      <fo:block>
        <xsl:value-of select="ancestor-or-self::article/articleinfo/title"/>
      </fo:block>
        </xsl:when>
        <xsl:when test="$position='center'">
        </xsl:when>
        <xsl:when test="$position='right'">
           <fo:block>
            <fo:external-graphic content-height="0.7cm">
              <xsl:attribute name="src">
                <xsl:call-template name="fo-external-image">
                  <xsl:with-param name="filename" select="$header.image.filename"/>
                </xsl:call-template>
              </xsl:attribute>
            </fo:external-graphic>
          </fo:block>
        </xsl:when>
        <xsl:when test="$sequence = 'first'">
        </xsl:when>
        <xsl:when test="$sequence = 'blank'">
        </xsl:when>
      </xsl:choose>
    </fo:block>
  </xsl:template>

  <!-- Aligning text to bottom border in header -->
  <xsl:template name="header.table">
    <xsl:param name="pageclass" select="''"/>
    <xsl:param name="sequence" select="''"/>
    <xsl:param name="gentext-key" select="''"/>

    <xsl:variable name="column1">
      <xsl:choose>
        <xsl:when test="$double.sided = 0">1</xsl:when>
        <xsl:when test="$sequence = 'first' or $sequence = 'odd'">1</xsl:when>
        <xsl:otherwise>3</xsl:otherwise>
      </xsl:choose>
    </xsl:variable>

    <xsl:variable name="column3">
      <xsl:choose>
        <xsl:when test="$double.sided = 0">3</xsl:when>
        <xsl:when test="$sequence = 'first' or $sequence = 'odd'">3</xsl:when>
        <xsl:otherwise>1</xsl:otherwise>
      </xsl:choose>
    </xsl:variable>

    <xsl:variable name="candidate">
      <fo:table table-layout="fixed" width="100%">
        <xsl:call-template name="head.sep.rule">
          <xsl:with-param name="pageclass" select="$pageclass"/>
          <xsl:with-param name="sequence" select="$sequence"/>
          <xsl:with-param name="gentext-key" select="$gentext-key"/>
        </xsl:call-template>
        <fo:table-column column-number="1">
          <xsl:attribute name="column-width">
            <xsl:text>proportional-column-width(</xsl:text>
            <xsl:call-template name="header.footer.width">
              <xsl:with-param name="location">header</xsl:with-param>
              <xsl:with-param name="position" select="$column1"/>
            </xsl:call-template>
            <xsl:text>)</xsl:text>
          </xsl:attribute>
        </fo:table-column>
        <fo:table-column column-number="2">
          <xsl:attribute name="column-width">
            <xsl:text>proportional-column-width(</xsl:text>
            <xsl:call-template name="header.footer.width">
              <xsl:with-param name="location">header</xsl:with-param>
              <xsl:with-param name="position" select="2"/>
            </xsl:call-template>
            <xsl:text>)</xsl:text>
          </xsl:attribute>
        </fo:table-column>
        <fo:table-column column-number="3">
          <xsl:attribute name="column-width">
            <xsl:text>proportional-column-width(</xsl:text>
            <xsl:call-template name="header.footer.width">
              <xsl:with-param name="location">header</xsl:with-param>
              <xsl:with-param name="position" select="$column3"/>
            </xsl:call-template>
            <xsl:text>)</xsl:text>
          </xsl:attribute>
        </fo:table-column>

        <fo:table-body>
          <fo:table-row height="14pt">
            <fo:table-cell text-align="left" display-align="after">
              <xsl:if test="$fop.extensions = 0">
                <xsl:attribute name="relative-align">baseline</xsl:attribute>
              </xsl:if>
              <fo:block>
                <xsl:call-template name="header.content">
                  <xsl:with-param name="pageclass" select="$pageclass"/>
                  <xsl:with-param name="sequence" select="$sequence"/>
                  <xsl:with-param name="position" select="'left'"/>
                  <xsl:with-param name="gentext-key" select="$gentext-key"/>
                </xsl:call-template>
              </fo:block>
            </fo:table-cell>
            <fo:table-cell text-align="center" display-align="after">
              <xsl:if test="$fop.extensions = 0">
                <xsl:attribute name="relative-align">baseline</xsl:attribute>
              </xsl:if>
              <fo:block>
                <xsl:call-template name="header.content">
                  <xsl:with-param name="pageclass" select="$pageclass"/>
                  <xsl:with-param name="sequence" select="$sequence"/>
                  <xsl:with-param name="position" select="'center'"/>
                  <xsl:with-param name="gentext-key" select="$gentext-key"/>
                </xsl:call-template>
              </fo:block>
            </fo:table-cell>
            <fo:table-cell text-align="right" display-align="after">
              <xsl:if test="$fop.extensions = 0">
                <xsl:attribute name="relative-align">baseline</xsl:attribute>
              </xsl:if>
              <fo:block>
                <xsl:call-template name="header.content">
                  <xsl:with-param name="pageclass" select="$pageclass"/>
                  <xsl:with-param name="sequence" select="$sequence"/>
                  <xsl:with-param name="position" select="'right'"/>
                  <xsl:with-param name="gentext-key" select="$gentext-key"/>
                </xsl:call-template>
              </fo:block>
            </fo:table-cell>
          </fo:table-row>
        </fo:table-body>
      </fo:table>
    </xsl:variable>

  <!-- Really output a header? -->
    <xsl:choose>
      <xsl:when test="$pageclass = 'titlepage' and $gentext-key = 'book'
                      and $sequence='first'">
        <!-- no, book titlepages have no headers at all -->
      </xsl:when>
      <xsl:when test="$sequence = 'first' and $gentext-key = 'article'">
        <!-- no, article titlepages have no headers at all -->
      </xsl:when>
      <xsl:when test="$sequence = 'blank' and $headers.on.blank.pages = 0">
        <!-- no output -->
      </xsl:when>
      <xsl:otherwise>
        <xsl:copy-of select="$candidate"/>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>

  <!-- Footer properties-->
  <!-- Footer content properties -->
  <xsl:attribute-set name="footer.content.properties">
    <xsl:attribute name="font-size">8pt</xsl:attribute>
  </xsl:attribute-set>
  <!-- Footer content itself -->
  <xsl:template name="footer.content">
    <xsl:param name="pageclass" select="''"/>
    <xsl:param name="sequence" select="''"/>
    <xsl:param name="position" select="''"/>
    <xsl:param name="gentext-key" select="''"/>
    <fo:block>
      <xsl:choose>
        <xsl:when test="$pageclass = 'titlepage'">
        </xsl:when>
        <xsl:when test="$position='left'">
          <fo:block>
            <fo:retrieve-marker retrieve-class-name="section.head.marker"
                                retrieve-position="first-including-carryover"
                                retrieve-boundary="page-sequence"/>
          </fo:block>
        </xsl:when>
        <xsl:when test="$position='center'">
          <fo:page-number/>
        </xsl:when>
        <xsl:when test="$position='right'">
          <fo:block>
            <xsl:text>Copyright © &CopyrightYear; Luxoft. All rights reserved.</xsl:text>
          </fo:block>
        </xsl:when>
        <xsl:otherwise>
          <!-- nop -->
        </xsl:otherwise>
      </xsl:choose>
    </fo:block>
  </xsl:template>

  <!-- Aligning text to top border in footer -->
  <xsl:template name="footer.table">
    <xsl:param name="pageclass" select="''"/>
    <xsl:param name="sequence" select="''"/>
    <xsl:param name="gentext-key" select="''"/>

    <xsl:variable name="column1">
      <xsl:choose>
        <xsl:when test="$double.sided = 0">1</xsl:when>
        <xsl:when test="$sequence = 'first' or $sequence = 'odd'">1</xsl:when>
        <xsl:otherwise>3</xsl:otherwise>
      </xsl:choose>
    </xsl:variable>

    <xsl:variable name="column3">
      <xsl:choose>
        <xsl:when test="$double.sided = 0">3</xsl:when>
        <xsl:when test="$sequence = 'first' or $sequence = 'odd'">3</xsl:when>
        <xsl:otherwise>1</xsl:otherwise>
      </xsl:choose>
    </xsl:variable>

    <xsl:variable name="candidate">
      <fo:table table-layout="fixed" width="100%">
        <xsl:call-template name="foot.sep.rule">
          <xsl:with-param name="pageclass" select="$pageclass"/>
          <xsl:with-param name="sequence" select="$sequence"/>
          <xsl:with-param name="gentext-key" select="$gentext-key"/>
        </xsl:call-template>
        <fo:table-column column-number="1">
          <xsl:attribute name="column-width">
            <xsl:text>proportional-column-width(</xsl:text>
            <xsl:call-template name="header.footer.width">
              <xsl:with-param name="location">footer</xsl:with-param>
              <xsl:with-param name="position" select="$column1"/>
            </xsl:call-template>
            <xsl:text>)</xsl:text>
          </xsl:attribute>
        </fo:table-column>
        <fo:table-column column-number="2">
          <xsl:attribute name="column-width">
            <xsl:text>proportional-column-width(</xsl:text>
            <xsl:call-template name="header.footer.width">
              <xsl:with-param name="location">footer</xsl:with-param>
              <xsl:with-param name="position" select="2"/>
            </xsl:call-template>
            <xsl:text>)</xsl:text>
          </xsl:attribute>
        </fo:table-column>
        <fo:table-column column-number="3">
          <xsl:attribute name="column-width">
            <xsl:text>proportional-column-width(</xsl:text>
            <xsl:call-template name="header.footer.width">
              <xsl:with-param name="location">footer</xsl:with-param>
              <xsl:with-param name="position" select="$column3"/>
            </xsl:call-template>
            <xsl:text>)</xsl:text>
          </xsl:attribute>
        </fo:table-column>

        <fo:table-body>
          <fo:table-row height="14pt">
            <fo:table-cell text-align="left" display-align="before">
              <xsl:if test="$fop.extensions = 0">
                <xsl:attribute name="relative-align">baseline</xsl:attribute>
              </xsl:if>
              <fo:block>
                <xsl:call-template name="footer.content">
                  <xsl:with-param name="pageclass" select="$pageclass"/>
                  <xsl:with-param name="sequence" select="$sequence"/>
                  <xsl:with-param name="position" select="'left'"/>
                  <xsl:with-param name="gentext-key" select="$gentext-key"/>
                </xsl:call-template>
              </fo:block>
            </fo:table-cell>
            <fo:table-cell text-align="center" display-align="before">
              <xsl:if test="$fop.extensions = 0">
                <xsl:attribute name="relative-align">baseline</xsl:attribute>
              </xsl:if>
              <fo:block>
                <xsl:call-template name="footer.content">
                  <xsl:with-param name="pageclass" select="$pageclass"/>
                  <xsl:with-param name="sequence" select="$sequence"/>
                  <xsl:with-param name="position" select="'center'"/>
                  <xsl:with-param name="gentext-key" select="$gentext-key"/>
                </xsl:call-template>
              </fo:block>
            </fo:table-cell>
            <fo:table-cell text-align="right" display-align="before">
              <xsl:if test="$fop.extensions = 0">
                <xsl:attribute name="relative-align">baseline</xsl:attribute>
              </xsl:if>
              <fo:block>
                <xsl:call-template name="footer.content">
                  <xsl:with-param name="pageclass" select="$pageclass"/>
                  <xsl:with-param name="sequence" select="$sequence"/>
                  <xsl:with-param name="position" select="'right'"/>
                  <xsl:with-param name="gentext-key" select="$gentext-key"/>
                </xsl:call-template>
              </fo:block>
            </fo:table-cell>
          </fo:table-row>
        </fo:table-body>
      </fo:table>
    </xsl:variable>

  <!-- Really output a footer? -->
    <xsl:choose>
      <xsl:when test="$pageclass = 'titlepage' and $gentext-key = 'book'
                      and $sequence='first'">
        <!-- no, book titlepages have no footers at all -->
      </xsl:when>
      <xsl:when test="$sequence = 'first' and $gentext-key = 'article'">
        <!-- no, article titlepages have no footers at all -->
      </xsl:when>
      <xsl:when test="$sequence = 'blank' and $footers.on.blank.pages = 0">
        <!-- no output -->
      </xsl:when>
      <xsl:otherwise>
        <xsl:copy-of select="$candidate"/>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>

</xsl:stylesheet>
