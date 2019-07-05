<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:fo="http://www.w3.org/1999/XSL/Format" version="1.0">

  <!-- Import the common stylesheet -->
  <xsl:import href="CommonPDFAdaptations.xsl"/>

  <!-- Import the stylesheet for the title page -->
  <xsl:import href="ArticleTitlepage.xsl"/>

  <!-- Display the last revision number on the title page inside the issuenum element.  -->
  <!-- In DocBook files the <issuenum> element shall be empty.                          -->
  <xsl:template match="issuenum" mode="article.titlepage.recto.auto.mode">
    <fo:block xmlns:fo="http://www.w3.org/1999/XSL/Format" xsl:use-attribute-sets="article.titlepage.recto.style" text-align="left">
      <xsl:text>Revision </xsl:text>
      <xsl:value-of select="ancestor-or-self::node()[self::article]/articleinfo/revhistory/revision/revnumber"/>
      <xsl:apply-templates select="." mode="article.titlepage.recto.mode"/>
    </fo:block>
  </xsl:template>

</xsl:stylesheet>
