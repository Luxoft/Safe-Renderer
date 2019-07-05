<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE stylesheet [
<!ENTITY % myents SYSTEM "../../../config/DocBookConfig.ent">
%myents;
]>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:fo="http://www.w3.org/1999/XSL/Format" version="1.0">

  <!-- Import the common stylesheet -->
  <xsl:import href="CommonPDFAdaptations.xsl"/>

  <!-- Import the stylesheet for the title page -->
  <xsl:import href="ChangeLogTitlepage.xsl"/>

  <!-- ***************  Additional  *********************  -->
  <xsl:attribute-set name="table.properties">
    <xsl:attribute name="hyphenate">false</xsl:attribute>
  </xsl:attribute-set>

  <!-- ***************  Automatic labelling  *********************  -->
  <!-- ***************************************************  -->
  <!-- If true (non-zero), unlabeled sections will be enumerated. -->
  <xsl:param name="section.autolabel" select="0"/>

  <!-- ***************  Tables  *********************  -->
  <!-- ***************************************************  -->
  <!-- cell padding for tables -->
  <xsl:attribute-set name="table.cell.padding">
    <xsl:attribute name="padding-left">4pt</xsl:attribute>
    <xsl:attribute name="padding-right">4pt</xsl:attribute>
    <xsl:attribute name="padding-top">6pt</xsl:attribute>
    <xsl:attribute name="padding-bottom">6pt</xsl:attribute>
  </xsl:attribute-set>

  <!-- ***************  ToC/LoT/Index Generation  *********************  -->
  <xsl:param name="toc.section.depth">3</xsl:param>

  <!-- ***************  Header and footer  *********************  -->
  <!-- Header properties -->
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
        <xsl:value-of select="ancestor-or-self::article/articleinfo/subtitle"/>
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

  <!-- Footer properties-->
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
        <xsl:text>Date: </xsl:text>
            <xsl:value-of select="ancestor-or-self::article/articleinfo/pubdate"/>
          </fo:block>
      <fo:block>
        <xsl:text>Release: </xsl:text>
            <xsl:value-of select="ancestor-or-self::article/articleinfo/issuenum"/>
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

  <!-- Add the word "Release" to the release number from the issuenum element on the title page.  -->
  <xsl:template match="issuenum" mode="article.titlepage.recto.auto.mode">
    <fo:block xmlns:fo="http://www.w3.org/1999/XSL/Format" xsl:use-attribute-sets="article.titlepage.recto.style" text-align="left">
      <xsl:text>Release </xsl:text>
      <xsl:apply-templates select="." mode="article.titlepage.recto.mode"/>
    </fo:block>
  </xsl:template>

</xsl:stylesheet>
