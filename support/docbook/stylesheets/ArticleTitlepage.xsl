<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:exsl="http://exslt.org/common" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" exclude-result-prefixes="exsl">

<!-- This stylesheet was created by template/titlepage.xsl-->

<xsl:template name="article.titlepage.before.recto">
</xsl:template>

<xsl:template name="article.titlepage.recto">
  <xsl:apply-templates mode="article.titlepage.recto.auto.mode" select="articleinfo/mediaobject"/>
  <xsl:apply-templates mode="article.titlepage.recto.auto.mode" select="artheader/mediaobject"/>
  <xsl:apply-templates mode="article.titlepage.recto.auto.mode" select="info/mediaobject"/>
  <xsl:choose>
    <xsl:when test="articleinfo/title">
      <xsl:apply-templates mode="article.titlepage.recto.auto.mode" select="articleinfo/title"/>
    </xsl:when>
    <xsl:when test="artheader/title">
      <xsl:apply-templates mode="article.titlepage.recto.auto.mode" select="artheader/title"/>
    </xsl:when>
    <xsl:when test="info/title">
      <xsl:apply-templates mode="article.titlepage.recto.auto.mode" select="info/title"/>
    </xsl:when>
    <xsl:when test="title">
      <xsl:apply-templates mode="article.titlepage.recto.auto.mode" select="title"/>
    </xsl:when>
  </xsl:choose>

  <xsl:choose>
    <xsl:when test="articleinfo/subtitle">
      <xsl:apply-templates mode="article.titlepage.recto.auto.mode" select="articleinfo/subtitle"/>
    </xsl:when>
    <xsl:when test="artheader/subtitle">
      <xsl:apply-templates mode="article.titlepage.recto.auto.mode" select="artheader/subtitle"/>
    </xsl:when>
    <xsl:when test="info/subtitle">
      <xsl:apply-templates mode="article.titlepage.recto.auto.mode" select="info/subtitle"/>
    </xsl:when>
    <xsl:when test="subtitle">
      <xsl:apply-templates mode="article.titlepage.recto.auto.mode" select="subtitle"/>
    </xsl:when>
  </xsl:choose>

  <xsl:apply-templates mode="article.titlepage.recto.auto.mode" select="articleinfo/pubdate"/>
  <xsl:apply-templates mode="article.titlepage.recto.auto.mode" select="artheader/pubdate"/>
  <xsl:apply-templates mode="article.titlepage.recto.auto.mode" select="info/pubdate"/>
  <xsl:apply-templates mode="article.titlepage.recto.auto.mode" select="articleinfo/issuenum"/>
  <xsl:apply-templates mode="article.titlepage.recto.auto.mode" select="artheader/issuenum"/>
  <xsl:apply-templates mode="article.titlepage.recto.auto.mode" select="info/issuenum"/>
</xsl:template>

<xsl:template name="article.titlepage.before.verso"><xsl:call-template name="component.toc.separator"/>
</xsl:template>

<xsl:template name="article.titlepage.verso">
  <xsl:apply-templates mode="article.titlepage.verso.auto.mode" select="articleinfo/legalnotice"/>
  <xsl:apply-templates mode="article.titlepage.verso.auto.mode" select="artheader/legalnotice"/>
  <xsl:apply-templates mode="article.titlepage.verso.auto.mode" select="info/legalnotice"/>
  <xsl:apply-templates mode="article.titlepage.verso.auto.mode" select="articleinfo/revhistory"/>
  <xsl:apply-templates mode="article.titlepage.verso.auto.mode" select="artheader/revhistory"/>
  <xsl:apply-templates mode="article.titlepage.verso.auto.mode" select="info/revhistory"/>
</xsl:template>

<xsl:template name="article.titlepage.separator"><xsl:call-template name="component.toc.separator"/>
</xsl:template>

<xsl:template name="article.titlepage">
  <fo:block xmlns:fo="http://www.w3.org/1999/XSL/Format" font-family="{$title.fontset}">
    <xsl:variable name="recto.content">
      <xsl:call-template name="article.titlepage.before.recto"/>
      <xsl:call-template name="article.titlepage.recto"/>
    </xsl:variable>
    <xsl:variable name="recto.elements.count">
      <xsl:choose>
        <xsl:when test="function-available('exsl:node-set')"><xsl:value-of select="count(exsl:node-set($recto.content)/*)"/></xsl:when>
        <xsl:when test="contains(system-property('xsl:vendor'), 'Apache Software Foundation')">
          <!--Xalan quirk--><xsl:value-of select="count(exsl:node-set($recto.content)/*)"/></xsl:when>
        <xsl:otherwise>1</xsl:otherwise>
      </xsl:choose>
    </xsl:variable>
    <xsl:if test="(normalize-space($recto.content) != '') or ($recto.elements.count &gt; 0)">
      <fo:block start-indent="0pt" text-align="center"><xsl:copy-of select="$recto.content"/></fo:block>
    </xsl:if>
    <xsl:variable name="verso.content">
      <xsl:call-template name="article.titlepage.before.verso"/>
      <xsl:call-template name="article.titlepage.verso"/>
    </xsl:variable>
    <xsl:variable name="verso.elements.count">
      <xsl:choose>
        <xsl:when test="function-available('exsl:node-set')"><xsl:value-of select="count(exsl:node-set($verso.content)/*)"/></xsl:when>
        <xsl:when test="contains(system-property('xsl:vendor'), 'Apache Software Foundation')">
          <!--Xalan quirk--><xsl:value-of select="count(exsl:node-set($verso.content)/*)"/></xsl:when>
        <xsl:otherwise>1</xsl:otherwise>
      </xsl:choose>
    </xsl:variable>
    <xsl:if test="(normalize-space($verso.content) != '') or ($verso.elements.count &gt; 0)">
      <fo:block start-indent="0pt" text-align="center"><xsl:copy-of select="$verso.content"/></fo:block>
    </xsl:if>
    <xsl:call-template name="article.titlepage.separator"/>
  </fo:block>
</xsl:template>

<xsl:template match="*" mode="article.titlepage.recto.mode">
  <!-- if an element isn't found in this mode, -->
  <!-- try the generic titlepage.mode -->
  <xsl:apply-templates select="." mode="titlepage.mode"/>
</xsl:template>

<xsl:template match="*" mode="article.titlepage.verso.mode">
  <!-- if an element isn't found in this mode, -->
  <!-- try the generic titlepage.mode -->
  <xsl:apply-templates select="." mode="titlepage.mode"/>
</xsl:template>

<xsl:template match="mediaobject" mode="article.titlepage.recto.auto.mode">
<fo:block xmlns:fo="http://www.w3.org/1999/XSL/Format" xsl:use-attribute-sets="article.titlepage.recto.style" space-before="1in">
<xsl:apply-templates select="." mode="article.titlepage.recto.mode"/>
</fo:block>
</xsl:template>

<xsl:template match="title" mode="article.titlepage.recto.auto.mode">
<fo:block xmlns:fo="http://www.w3.org/1999/XSL/Format" xsl:use-attribute-sets="article.titlepage.recto.style" keep-with-next.within-column="always" font-size="36pt" font-weight="bold" space-before="2in">
<xsl:call-template name="component.title">
<xsl:with-param name="node" select="ancestor-or-self::article[1]"/>
</xsl:call-template>
</fo:block>
</xsl:template>

<xsl:template match="subtitle" mode="article.titlepage.recto.auto.mode">
<fo:block xmlns:fo="http://www.w3.org/1999/XSL/Format" xsl:use-attribute-sets="article.titlepage.recto.style" font-size="17.28pt" space-before="0.7in" space-after="2in">
<xsl:apply-templates select="." mode="article.titlepage.recto.mode"/>
</fo:block>
</xsl:template>

<xsl:template match="pubdate" mode="article.titlepage.recto.auto.mode">
<fo:block xmlns:fo="http://www.w3.org/1999/XSL/Format" xsl:use-attribute-sets="article.titlepage.recto.style" text-align="left">
<xsl:apply-templates select="." mode="article.titlepage.recto.mode"/>
</fo:block>
</xsl:template>

<xsl:template match="issuenum" mode="article.titlepage.recto.auto.mode">
<fo:block xmlns:fo="http://www.w3.org/1999/XSL/Format" xsl:use-attribute-sets="article.titlepage.recto.style" text-align="left">
<xsl:apply-templates select="." mode="article.titlepage.recto.mode"/>
</fo:block>
</xsl:template>

<xsl:template match="legalnotice" mode="article.titlepage.verso.auto.mode">
<fo:block xmlns:fo="http://www.w3.org/1999/XSL/Format" xsl:use-attribute-sets="article.titlepage.verso.style" text-align="start" font-family="{$body.fontset}">
<xsl:apply-templates select="." mode="article.titlepage.verso.mode"/>
</fo:block>
</xsl:template>

<xsl:template match="revhistory" mode="article.titlepage.verso.auto.mode">
<fo:block xmlns:fo="http://www.w3.org/1999/XSL/Format" xsl:use-attribute-sets="article.titlepage.verso.style" space-before="0.6in">
<xsl:apply-templates select="." mode="article.titlepage.verso.mode"/>
</fo:block>
</xsl:template>

<xsl:template name="table.of.contents.titlepage.recto">
  <fo:block xmlns:fo="http://www.w3.org/1999/XSL/Format" xsl:use-attribute-sets="table.of.contents.titlepage.recto.style" space-before.minimum="1em" space-before.optimum="1.5em" space-before.maximum="2em" space-after="0.5em" start-indent="0pt" font-size="17.28pt" font-weight="bold" font-family="{$title.fontset}">
<xsl:call-template name="gentext">
<xsl:with-param name="key" select="'TableofContents'"/>
</xsl:call-template></fo:block>
</xsl:template>

<xsl:template name="table.of.contents.titlepage.verso">
</xsl:template>

<xsl:template name="table.of.contents.titlepage.separator">
</xsl:template>

<xsl:template name="table.of.contents.titlepage.before.recto">
</xsl:template>

<xsl:template name="table.of.contents.titlepage.before.verso">
</xsl:template>

<xsl:template name="table.of.contents.titlepage">
  <fo:block xmlns:fo="http://www.w3.org/1999/XSL/Format">
    <xsl:variable name="recto.content">
      <xsl:call-template name="table.of.contents.titlepage.before.recto"/>
      <xsl:call-template name="table.of.contents.titlepage.recto"/>
    </xsl:variable>
    <xsl:variable name="recto.elements.count">
      <xsl:choose>
        <xsl:when test="function-available('exsl:node-set')"><xsl:value-of select="count(exsl:node-set($recto.content)/*)"/></xsl:when>
        <xsl:when test="contains(system-property('xsl:vendor'), 'Apache Software Foundation')">
          <!--Xalan quirk--><xsl:value-of select="count(exsl:node-set($recto.content)/*)"/></xsl:when>
        <xsl:otherwise>1</xsl:otherwise>
      </xsl:choose>
    </xsl:variable>
    <xsl:if test="(normalize-space($recto.content) != '') or ($recto.elements.count &gt; 0)">
      <fo:block><xsl:copy-of select="$recto.content"/></fo:block>
    </xsl:if>
    <xsl:variable name="verso.content">
      <xsl:call-template name="table.of.contents.titlepage.before.verso"/>
      <xsl:call-template name="table.of.contents.titlepage.verso"/>
    </xsl:variable>
    <xsl:variable name="verso.elements.count">
      <xsl:choose>
        <xsl:when test="function-available('exsl:node-set')"><xsl:value-of select="count(exsl:node-set($verso.content)/*)"/></xsl:when>
        <xsl:when test="contains(system-property('xsl:vendor'), 'Apache Software Foundation')">
          <!--Xalan quirk--><xsl:value-of select="count(exsl:node-set($verso.content)/*)"/></xsl:when>
        <xsl:otherwise>1</xsl:otherwise>
      </xsl:choose>
    </xsl:variable>
    <xsl:if test="(normalize-space($verso.content) != '') or ($verso.elements.count &gt; 0)">
      <fo:block><xsl:copy-of select="$verso.content"/></fo:block>
    </xsl:if>
    <xsl:call-template name="table.of.contents.titlepage.separator"/>
  </fo:block>
</xsl:template>

<xsl:template match="*" mode="table.of.contents.titlepage.recto.mode">
  <!-- if an element isn't found in this mode, -->
  <!-- try the generic titlepage.mode -->
  <xsl:apply-templates select="." mode="titlepage.mode"/>
</xsl:template>

<xsl:template match="*" mode="table.of.contents.titlepage.verso.mode">
  <!-- if an element isn't found in this mode, -->
  <!-- try the generic titlepage.mode -->
  <xsl:apply-templates select="." mode="titlepage.mode"/>
</xsl:template>

<xsl:template name="list.of.tables.titlepage.recto">
  <fo:block xmlns:fo="http://www.w3.org/1999/XSL/Format" xsl:use-attribute-sets="list.of.tables.titlepage.recto.style" space-before.minimum="1em" space-before.optimum="1.5em" space-before.maximum="2em" space-after="0.5em" start-indent="0pt" font-size="17.28pt" font-weight="bold" font-family="{$title.fontset}">
<xsl:call-template name="gentext">
<xsl:with-param name="key" select="'ListofTables'"/>
</xsl:call-template></fo:block>
</xsl:template>

<xsl:template name="list.of.tables.titlepage.verso">
</xsl:template>

<xsl:template name="list.of.tables.titlepage.separator">
</xsl:template>

<xsl:template name="list.of.tables.titlepage.before.recto">
</xsl:template>

<xsl:template name="list.of.tables.titlepage.before.verso">
</xsl:template>

<xsl:template name="list.of.tables.titlepage">
  <fo:block xmlns:fo="http://www.w3.org/1999/XSL/Format">
    <xsl:variable name="recto.content">
      <xsl:call-template name="list.of.tables.titlepage.before.recto"/>
      <xsl:call-template name="list.of.tables.titlepage.recto"/>
    </xsl:variable>
    <xsl:variable name="recto.elements.count">
      <xsl:choose>
        <xsl:when test="function-available('exsl:node-set')"><xsl:value-of select="count(exsl:node-set($recto.content)/*)"/></xsl:when>
        <xsl:when test="contains(system-property('xsl:vendor'), 'Apache Software Foundation')">
          <!--Xalan quirk--><xsl:value-of select="count(exsl:node-set($recto.content)/*)"/></xsl:when>
        <xsl:otherwise>1</xsl:otherwise>
      </xsl:choose>
    </xsl:variable>
    <xsl:if test="(normalize-space($recto.content) != '') or ($recto.elements.count &gt; 0)">
      <fo:block><xsl:copy-of select="$recto.content"/></fo:block>
    </xsl:if>
    <xsl:variable name="verso.content">
      <xsl:call-template name="list.of.tables.titlepage.before.verso"/>
      <xsl:call-template name="list.of.tables.titlepage.verso"/>
    </xsl:variable>
    <xsl:variable name="verso.elements.count">
      <xsl:choose>
        <xsl:when test="function-available('exsl:node-set')"><xsl:value-of select="count(exsl:node-set($verso.content)/*)"/></xsl:when>
        <xsl:when test="contains(system-property('xsl:vendor'), 'Apache Software Foundation')">
          <!--Xalan quirk--><xsl:value-of select="count(exsl:node-set($verso.content)/*)"/></xsl:when>
        <xsl:otherwise>1</xsl:otherwise>
      </xsl:choose>
    </xsl:variable>
    <xsl:if test="(normalize-space($verso.content) != '') or ($verso.elements.count &gt; 0)">
      <fo:block><xsl:copy-of select="$verso.content"/></fo:block>
    </xsl:if>
    <xsl:call-template name="list.of.tables.titlepage.separator"/>
  </fo:block>
</xsl:template>

<xsl:template match="*" mode="list.of.tables.titlepage.recto.mode">
  <!-- if an element isn't found in this mode, -->
  <!-- try the generic titlepage.mode -->
  <xsl:apply-templates select="." mode="titlepage.mode"/>
</xsl:template>

<xsl:template match="*" mode="list.of.tables.titlepage.verso.mode">
  <!-- if an element isn't found in this mode, -->
  <!-- try the generic titlepage.mode -->
  <xsl:apply-templates select="." mode="titlepage.mode"/>
</xsl:template>

<xsl:template name="list.of.figures.titlepage.recto">
  <fo:block xmlns:fo="http://www.w3.org/1999/XSL/Format" xsl:use-attribute-sets="list.of.figures.titlepage.recto.style" space-before.minimum="1em" space-before.optimum="1.5em" space-before.maximum="2em" space-after="0.5em" start-indent="0pt" font-size="17.28pt" font-weight="bold" font-family="{$title.fontset}">
<xsl:call-template name="gentext">
<xsl:with-param name="key" select="'ListofFigures'"/>
</xsl:call-template></fo:block>
</xsl:template>

<xsl:template name="list.of.figures.titlepage.verso">
</xsl:template>

<xsl:template name="list.of.figures.titlepage.separator">
</xsl:template>

<xsl:template name="list.of.figures.titlepage.before.recto">
</xsl:template>

<xsl:template name="list.of.figures.titlepage.before.verso">
</xsl:template>

<xsl:template name="list.of.figures.titlepage">
  <fo:block xmlns:fo="http://www.w3.org/1999/XSL/Format">
    <xsl:variable name="recto.content">
      <xsl:call-template name="list.of.figures.titlepage.before.recto"/>
      <xsl:call-template name="list.of.figures.titlepage.recto"/>
    </xsl:variable>
    <xsl:variable name="recto.elements.count">
      <xsl:choose>
        <xsl:when test="function-available('exsl:node-set')"><xsl:value-of select="count(exsl:node-set($recto.content)/*)"/></xsl:when>
        <xsl:when test="contains(system-property('xsl:vendor'), 'Apache Software Foundation')">
          <!--Xalan quirk--><xsl:value-of select="count(exsl:node-set($recto.content)/*)"/></xsl:when>
        <xsl:otherwise>1</xsl:otherwise>
      </xsl:choose>
    </xsl:variable>
    <xsl:if test="(normalize-space($recto.content) != '') or ($recto.elements.count &gt; 0)">
      <fo:block><xsl:copy-of select="$recto.content"/></fo:block>
    </xsl:if>
    <xsl:variable name="verso.content">
      <xsl:call-template name="list.of.figures.titlepage.before.verso"/>
      <xsl:call-template name="list.of.figures.titlepage.verso"/>
    </xsl:variable>
    <xsl:variable name="verso.elements.count">
      <xsl:choose>
        <xsl:when test="function-available('exsl:node-set')"><xsl:value-of select="count(exsl:node-set($verso.content)/*)"/></xsl:when>
        <xsl:when test="contains(system-property('xsl:vendor'), 'Apache Software Foundation')">
          <!--Xalan quirk--><xsl:value-of select="count(exsl:node-set($verso.content)/*)"/></xsl:when>
        <xsl:otherwise>1</xsl:otherwise>
      </xsl:choose>
    </xsl:variable>
    <xsl:if test="(normalize-space($verso.content) != '') or ($verso.elements.count &gt; 0)">
      <fo:block><xsl:copy-of select="$verso.content"/></fo:block>
    </xsl:if>
    <xsl:call-template name="list.of.figures.titlepage.separator"/>
  </fo:block>
</xsl:template>

<xsl:template match="*" mode="list.of.figures.titlepage.recto.mode">
  <!-- if an element isn't found in this mode, -->
  <!-- try the generic titlepage.mode -->
  <xsl:apply-templates select="." mode="titlepage.mode"/>
</xsl:template>

<xsl:template match="*" mode="list.of.figures.titlepage.verso.mode">
  <!-- if an element isn't found in this mode, -->
  <!-- try the generic titlepage.mode -->
  <xsl:apply-templates select="." mode="titlepage.mode"/>
</xsl:template>

<xsl:template name="list.of.examples.titlepage.recto">
  <fo:block xmlns:fo="http://www.w3.org/1999/XSL/Format" xsl:use-attribute-sets="list.of.examples.titlepage.recto.style" space-before.minimum="1em" space-before.optimum="1.5em" space-before.maximum="2em" space-after="0.5em" start-indent="0pt" font-size="17.28pt" font-weight="bold" font-family="{$title.fontset}">
<xsl:call-template name="gentext">
<xsl:with-param name="key" select="'ListofExamples'"/>
</xsl:call-template></fo:block>
</xsl:template>

<xsl:template name="list.of.examples.titlepage.verso">
</xsl:template>

<xsl:template name="list.of.examples.titlepage.separator">
</xsl:template>

<xsl:template name="list.of.examples.titlepage.before.recto">
</xsl:template>

<xsl:template name="list.of.examples.titlepage.before.verso">
</xsl:template>

<xsl:template name="list.of.examples.titlepage">
  <fo:block xmlns:fo="http://www.w3.org/1999/XSL/Format">
    <xsl:variable name="recto.content">
      <xsl:call-template name="list.of.examples.titlepage.before.recto"/>
      <xsl:call-template name="list.of.examples.titlepage.recto"/>
    </xsl:variable>
    <xsl:variable name="recto.elements.count">
      <xsl:choose>
        <xsl:when test="function-available('exsl:node-set')"><xsl:value-of select="count(exsl:node-set($recto.content)/*)"/></xsl:when>
        <xsl:when test="contains(system-property('xsl:vendor'), 'Apache Software Foundation')">
          <!--Xalan quirk--><xsl:value-of select="count(exsl:node-set($recto.content)/*)"/></xsl:when>
        <xsl:otherwise>1</xsl:otherwise>
      </xsl:choose>
    </xsl:variable>
    <xsl:if test="(normalize-space($recto.content) != '') or ($recto.elements.count &gt; 0)">
      <fo:block><xsl:copy-of select="$recto.content"/></fo:block>
    </xsl:if>
    <xsl:variable name="verso.content">
      <xsl:call-template name="list.of.examples.titlepage.before.verso"/>
      <xsl:call-template name="list.of.examples.titlepage.verso"/>
    </xsl:variable>
    <xsl:variable name="verso.elements.count">
      <xsl:choose>
        <xsl:when test="function-available('exsl:node-set')"><xsl:value-of select="count(exsl:node-set($verso.content)/*)"/></xsl:when>
        <xsl:when test="contains(system-property('xsl:vendor'), 'Apache Software Foundation')">
          <!--Xalan quirk--><xsl:value-of select="count(exsl:node-set($verso.content)/*)"/></xsl:when>
        <xsl:otherwise>1</xsl:otherwise>
      </xsl:choose>
    </xsl:variable>
    <xsl:if test="(normalize-space($verso.content) != '') or ($verso.elements.count &gt; 0)">
      <fo:block><xsl:copy-of select="$verso.content"/></fo:block>
    </xsl:if>
    <xsl:call-template name="list.of.examples.titlepage.separator"/>
  </fo:block>
</xsl:template>

<xsl:template match="*" mode="list.of.examples.titlepage.recto.mode">
  <!-- if an element isn't found in this mode, -->
  <!-- try the generic titlepage.mode -->
  <xsl:apply-templates select="." mode="titlepage.mode"/>
</xsl:template>

<xsl:template match="*" mode="list.of.examples.titlepage.verso.mode">
  <!-- if an element isn't found in this mode, -->
  <!-- try the generic titlepage.mode -->
  <xsl:apply-templates select="." mode="titlepage.mode"/>
</xsl:template>

<xsl:template name="list.of.equations.titlepage.recto">
  <fo:block xmlns:fo="http://www.w3.org/1999/XSL/Format" xsl:use-attribute-sets="list.of.equations.titlepage.recto.style" space-before.minimum="1em" space-before.optimum="1.5em" space-before.maximum="2em" space-after="0.5em" start-indent="0pt" font-size="17.28pt" font-weight="bold" font-family="{$title.fontset}">
<xsl:call-template name="gentext">
<xsl:with-param name="key" select="'ListofEquations'"/>
</xsl:call-template></fo:block>
</xsl:template>

<xsl:template name="list.of.equations.titlepage.verso">
</xsl:template>

<xsl:template name="list.of.equations.titlepage.separator">
</xsl:template>

<xsl:template name="list.of.equations.titlepage.before.recto">
</xsl:template>

<xsl:template name="list.of.equations.titlepage.before.verso">
</xsl:template>

<xsl:template name="list.of.equations.titlepage">
  <fo:block xmlns:fo="http://www.w3.org/1999/XSL/Format">
    <xsl:variable name="recto.content">
      <xsl:call-template name="list.of.equations.titlepage.before.recto"/>
      <xsl:call-template name="list.of.equations.titlepage.recto"/>
    </xsl:variable>
    <xsl:variable name="recto.elements.count">
      <xsl:choose>
        <xsl:when test="function-available('exsl:node-set')"><xsl:value-of select="count(exsl:node-set($recto.content)/*)"/></xsl:when>
        <xsl:when test="contains(system-property('xsl:vendor'), 'Apache Software Foundation')">
          <!--Xalan quirk--><xsl:value-of select="count(exsl:node-set($recto.content)/*)"/></xsl:when>
        <xsl:otherwise>1</xsl:otherwise>
      </xsl:choose>
    </xsl:variable>
    <xsl:if test="(normalize-space($recto.content) != '') or ($recto.elements.count &gt; 0)">
      <fo:block><xsl:copy-of select="$recto.content"/></fo:block>
    </xsl:if>
    <xsl:variable name="verso.content">
      <xsl:call-template name="list.of.equations.titlepage.before.verso"/>
      <xsl:call-template name="list.of.equations.titlepage.verso"/>
    </xsl:variable>
    <xsl:variable name="verso.elements.count">
      <xsl:choose>
        <xsl:when test="function-available('exsl:node-set')"><xsl:value-of select="count(exsl:node-set($verso.content)/*)"/></xsl:when>
        <xsl:when test="contains(system-property('xsl:vendor'), 'Apache Software Foundation')">
          <!--Xalan quirk--><xsl:value-of select="count(exsl:node-set($verso.content)/*)"/></xsl:when>
        <xsl:otherwise>1</xsl:otherwise>
      </xsl:choose>
    </xsl:variable>
    <xsl:if test="(normalize-space($verso.content) != '') or ($verso.elements.count &gt; 0)">
      <fo:block><xsl:copy-of select="$verso.content"/></fo:block>
    </xsl:if>
    <xsl:call-template name="list.of.equations.titlepage.separator"/>
  </fo:block>
</xsl:template>

<xsl:template match="*" mode="list.of.equations.titlepage.recto.mode">
  <!-- if an element isn't found in this mode, -->
  <!-- try the generic titlepage.mode -->
  <xsl:apply-templates select="." mode="titlepage.mode"/>
</xsl:template>

<xsl:template match="*" mode="list.of.equations.titlepage.verso.mode">
  <!-- if an element isn't found in this mode, -->
  <!-- try the generic titlepage.mode -->
  <xsl:apply-templates select="." mode="titlepage.mode"/>
</xsl:template>

<xsl:template name="list.of.procedures.titlepage.recto">
  <fo:block xmlns:fo="http://www.w3.org/1999/XSL/Format" xsl:use-attribute-sets="list.of.procedures.titlepage.recto.style" space-before.minimum="1em" space-before.optimum="1.5em" space-before.maximum="2em" space-after="0.5em" start-indent="0pt" font-size="17.28pt" font-weight="bold" font-family="{$title.fontset}">
<xsl:call-template name="gentext">
<xsl:with-param name="key" select="'ListofProcedures'"/>
</xsl:call-template></fo:block>
</xsl:template>

<xsl:template name="list.of.procedures.titlepage.verso">
</xsl:template>

<xsl:template name="list.of.procedures.titlepage.separator">
</xsl:template>

<xsl:template name="list.of.procedures.titlepage.before.recto">
</xsl:template>

<xsl:template name="list.of.procedures.titlepage.before.verso">
</xsl:template>

<xsl:template name="list.of.procedures.titlepage">
  <fo:block xmlns:fo="http://www.w3.org/1999/XSL/Format">
    <xsl:variable name="recto.content">
      <xsl:call-template name="list.of.procedures.titlepage.before.recto"/>
      <xsl:call-template name="list.of.procedures.titlepage.recto"/>
    </xsl:variable>
    <xsl:variable name="recto.elements.count">
      <xsl:choose>
        <xsl:when test="function-available('exsl:node-set')"><xsl:value-of select="count(exsl:node-set($recto.content)/*)"/></xsl:when>
        <xsl:when test="contains(system-property('xsl:vendor'), 'Apache Software Foundation')">
          <!--Xalan quirk--><xsl:value-of select="count(exsl:node-set($recto.content)/*)"/></xsl:when>
        <xsl:otherwise>1</xsl:otherwise>
      </xsl:choose>
    </xsl:variable>
    <xsl:if test="(normalize-space($recto.content) != '') or ($recto.elements.count &gt; 0)">
      <fo:block><xsl:copy-of select="$recto.content"/></fo:block>
    </xsl:if>
    <xsl:variable name="verso.content">
      <xsl:call-template name="list.of.procedures.titlepage.before.verso"/>
      <xsl:call-template name="list.of.procedures.titlepage.verso"/>
    </xsl:variable>
    <xsl:variable name="verso.elements.count">
      <xsl:choose>
        <xsl:when test="function-available('exsl:node-set')"><xsl:value-of select="count(exsl:node-set($verso.content)/*)"/></xsl:when>
        <xsl:when test="contains(system-property('xsl:vendor'), 'Apache Software Foundation')">
          <!--Xalan quirk--><xsl:value-of select="count(exsl:node-set($verso.content)/*)"/></xsl:when>
        <xsl:otherwise>1</xsl:otherwise>
      </xsl:choose>
    </xsl:variable>
    <xsl:if test="(normalize-space($verso.content) != '') or ($verso.elements.count &gt; 0)">
      <fo:block><xsl:copy-of select="$verso.content"/></fo:block>
    </xsl:if>
    <xsl:call-template name="list.of.procedures.titlepage.separator"/>
  </fo:block>
</xsl:template>

<xsl:template match="*" mode="list.of.procedures.titlepage.recto.mode">
  <!-- if an element isn't found in this mode, -->
  <!-- try the generic titlepage.mode -->
  <xsl:apply-templates select="." mode="titlepage.mode"/>
</xsl:template>

<xsl:template match="*" mode="list.of.procedures.titlepage.verso.mode">
  <!-- if an element isn't found in this mode, -->
  <!-- try the generic titlepage.mode -->
  <xsl:apply-templates select="." mode="titlepage.mode"/>
</xsl:template>

<xsl:template name="list.of.unknowns.titlepage.recto">
  <fo:block xmlns:fo="http://www.w3.org/1999/XSL/Format" xsl:use-attribute-sets="list.of.unknowns.titlepage.recto.style" space-before.minimum="1em" space-before.optimum="1.5em" space-before.maximum="2em" space-after="0.5em" start-indent="0pt" font-size="17.28pt" font-weight="bold" font-family="{$title.fontset}">
<xsl:call-template name="gentext">
<xsl:with-param name="key" select="'ListofUnknown'"/>
</xsl:call-template></fo:block>
</xsl:template>

<xsl:template name="list.of.unknowns.titlepage.verso">
</xsl:template>

<xsl:template name="list.of.unknowns.titlepage.separator">
</xsl:template>

<xsl:template name="list.of.unknowns.titlepage.before.recto">
</xsl:template>

<xsl:template name="list.of.unknowns.titlepage.before.verso">
</xsl:template>

<xsl:template name="list.of.unknowns.titlepage">
  <fo:block xmlns:fo="http://www.w3.org/1999/XSL/Format">
    <xsl:variable name="recto.content">
      <xsl:call-template name="list.of.unknowns.titlepage.before.recto"/>
      <xsl:call-template name="list.of.unknowns.titlepage.recto"/>
    </xsl:variable>
    <xsl:variable name="recto.elements.count">
      <xsl:choose>
        <xsl:when test="function-available('exsl:node-set')"><xsl:value-of select="count(exsl:node-set($recto.content)/*)"/></xsl:when>
        <xsl:when test="contains(system-property('xsl:vendor'), 'Apache Software Foundation')">
          <!--Xalan quirk--><xsl:value-of select="count(exsl:node-set($recto.content)/*)"/></xsl:when>
        <xsl:otherwise>1</xsl:otherwise>
      </xsl:choose>
    </xsl:variable>
    <xsl:if test="(normalize-space($recto.content) != '') or ($recto.elements.count &gt; 0)">
      <fo:block><xsl:copy-of select="$recto.content"/></fo:block>
    </xsl:if>
    <xsl:variable name="verso.content">
      <xsl:call-template name="list.of.unknowns.titlepage.before.verso"/>
      <xsl:call-template name="list.of.unknowns.titlepage.verso"/>
    </xsl:variable>
    <xsl:variable name="verso.elements.count">
      <xsl:choose>
        <xsl:when test="function-available('exsl:node-set')"><xsl:value-of select="count(exsl:node-set($verso.content)/*)"/></xsl:when>
        <xsl:when test="contains(system-property('xsl:vendor'), 'Apache Software Foundation')">
          <!--Xalan quirk--><xsl:value-of select="count(exsl:node-set($verso.content)/*)"/></xsl:when>
        <xsl:otherwise>1</xsl:otherwise>
      </xsl:choose>
    </xsl:variable>
    <xsl:if test="(normalize-space($verso.content) != '') or ($verso.elements.count &gt; 0)">
      <fo:block><xsl:copy-of select="$verso.content"/></fo:block>
    </xsl:if>
    <xsl:call-template name="list.of.unknowns.titlepage.separator"/>
  </fo:block>
</xsl:template>

<xsl:template match="*" mode="list.of.unknowns.titlepage.recto.mode">
  <!-- if an element isn't found in this mode, -->
  <!-- try the generic titlepage.mode -->
  <xsl:apply-templates select="." mode="titlepage.mode"/>
</xsl:template>

<xsl:template match="*" mode="list.of.unknowns.titlepage.verso.mode">
  <!-- if an element isn't found in this mode, -->
  <!-- try the generic titlepage.mode -->
  <xsl:apply-templates select="." mode="titlepage.mode"/>
</xsl:template>

<xsl:template name="component.list.of.tables.titlepage.recto">
  <fo:block xmlns:fo="http://www.w3.org/1999/XSL/Format" xsl:use-attribute-sets="component.list.of.tables.titlepage.recto.style" space-before.minimum="1em" space-before.optimum="1em" space-before.maximum="1em" space-after="0.5em" margin-left="{$title.margin.left}" font-size="12pt" font-weight="bold" font-family="{$title.fontset}">
<xsl:call-template name="gentext">
<xsl:with-param name="key" select="'ListofTables'"/>
</xsl:call-template></fo:block>
</xsl:template>

<xsl:template name="component.list.of.tables.titlepage.verso">
</xsl:template>

<xsl:template name="component.list.of.tables.titlepage.separator">
</xsl:template>

<xsl:template name="component.list.of.tables.titlepage.before.recto">
</xsl:template>

<xsl:template name="component.list.of.tables.titlepage.before.verso">
</xsl:template>

<xsl:template name="component.list.of.tables.titlepage">
  <fo:block xmlns:fo="http://www.w3.org/1999/XSL/Format">
    <xsl:variable name="recto.content">
      <xsl:call-template name="component.list.of.tables.titlepage.before.recto"/>
      <xsl:call-template name="component.list.of.tables.titlepage.recto"/>
    </xsl:variable>
    <xsl:variable name="recto.elements.count">
      <xsl:choose>
        <xsl:when test="function-available('exsl:node-set')"><xsl:value-of select="count(exsl:node-set($recto.content)/*)"/></xsl:when>
        <xsl:when test="contains(system-property('xsl:vendor'), 'Apache Software Foundation')">
          <!--Xalan quirk--><xsl:value-of select="count(exsl:node-set($recto.content)/*)"/></xsl:when>
        <xsl:otherwise>1</xsl:otherwise>
      </xsl:choose>
    </xsl:variable>
    <xsl:if test="(normalize-space($recto.content) != '') or ($recto.elements.count &gt; 0)">
      <fo:block><xsl:copy-of select="$recto.content"/></fo:block>
    </xsl:if>
    <xsl:variable name="verso.content">
      <xsl:call-template name="component.list.of.tables.titlepage.before.verso"/>
      <xsl:call-template name="component.list.of.tables.titlepage.verso"/>
    </xsl:variable>
    <xsl:variable name="verso.elements.count">
      <xsl:choose>
        <xsl:when test="function-available('exsl:node-set')"><xsl:value-of select="count(exsl:node-set($verso.content)/*)"/></xsl:when>
        <xsl:when test="contains(system-property('xsl:vendor'), 'Apache Software Foundation')">
          <!--Xalan quirk--><xsl:value-of select="count(exsl:node-set($verso.content)/*)"/></xsl:when>
        <xsl:otherwise>1</xsl:otherwise>
      </xsl:choose>
    </xsl:variable>
    <xsl:if test="(normalize-space($verso.content) != '') or ($verso.elements.count &gt; 0)">
      <fo:block><xsl:copy-of select="$verso.content"/></fo:block>
    </xsl:if>
    <xsl:call-template name="component.list.of.tables.titlepage.separator"/>
  </fo:block>
</xsl:template>

<xsl:template match="*" mode="component.list.of.tables.titlepage.recto.mode">
  <!-- if an element isn't found in this mode, -->
  <!-- try the generic titlepage.mode -->
  <xsl:apply-templates select="." mode="titlepage.mode"/>
</xsl:template>

<xsl:template match="*" mode="component.list.of.tables.titlepage.verso.mode">
  <!-- if an element isn't found in this mode, -->
  <!-- try the generic titlepage.mode -->
  <xsl:apply-templates select="." mode="titlepage.mode"/>
</xsl:template>

<xsl:template name="component.list.of.figures.titlepage.recto">
  <fo:block xmlns:fo="http://www.w3.org/1999/XSL/Format" xsl:use-attribute-sets="component.list.of.figures.titlepage.recto.style" space-before.minimum="1em" space-before.optimum="1em" space-before.maximum="1em" space-after="0.5em" margin-left="{$title.margin.left}" font-size="12pt" font-weight="bold" font-family="{$title.fontset}">
<xsl:call-template name="gentext">
<xsl:with-param name="key" select="'ListofFigures'"/>
</xsl:call-template></fo:block>
</xsl:template>

<xsl:template name="component.list.of.figures.titlepage.verso">
</xsl:template>

<xsl:template name="component.list.of.figures.titlepage.separator">
</xsl:template>

<xsl:template name="component.list.of.figures.titlepage.before.recto">
</xsl:template>

<xsl:template name="component.list.of.figures.titlepage.before.verso">
</xsl:template>

<xsl:template name="component.list.of.figures.titlepage">
  <fo:block xmlns:fo="http://www.w3.org/1999/XSL/Format">
    <xsl:variable name="recto.content">
      <xsl:call-template name="component.list.of.figures.titlepage.before.recto"/>
      <xsl:call-template name="component.list.of.figures.titlepage.recto"/>
    </xsl:variable>
    <xsl:variable name="recto.elements.count">
      <xsl:choose>
        <xsl:when test="function-available('exsl:node-set')"><xsl:value-of select="count(exsl:node-set($recto.content)/*)"/></xsl:when>
        <xsl:when test="contains(system-property('xsl:vendor'), 'Apache Software Foundation')">
          <!--Xalan quirk--><xsl:value-of select="count(exsl:node-set($recto.content)/*)"/></xsl:when>
        <xsl:otherwise>1</xsl:otherwise>
      </xsl:choose>
    </xsl:variable>
    <xsl:if test="(normalize-space($recto.content) != '') or ($recto.elements.count &gt; 0)">
      <fo:block><xsl:copy-of select="$recto.content"/></fo:block>
    </xsl:if>
    <xsl:variable name="verso.content">
      <xsl:call-template name="component.list.of.figures.titlepage.before.verso"/>
      <xsl:call-template name="component.list.of.figures.titlepage.verso"/>
    </xsl:variable>
    <xsl:variable name="verso.elements.count">
      <xsl:choose>
        <xsl:when test="function-available('exsl:node-set')"><xsl:value-of select="count(exsl:node-set($verso.content)/*)"/></xsl:when>
        <xsl:when test="contains(system-property('xsl:vendor'), 'Apache Software Foundation')">
          <!--Xalan quirk--><xsl:value-of select="count(exsl:node-set($verso.content)/*)"/></xsl:when>
        <xsl:otherwise>1</xsl:otherwise>
      </xsl:choose>
    </xsl:variable>
    <xsl:if test="(normalize-space($verso.content) != '') or ($verso.elements.count &gt; 0)">
      <fo:block><xsl:copy-of select="$verso.content"/></fo:block>
    </xsl:if>
    <xsl:call-template name="component.list.of.figures.titlepage.separator"/>
  </fo:block>
</xsl:template>

<xsl:template match="*" mode="component.list.of.figures.titlepage.recto.mode">
  <!-- if an element isn't found in this mode, -->
  <!-- try the generic titlepage.mode -->
  <xsl:apply-templates select="." mode="titlepage.mode"/>
</xsl:template>

<xsl:template match="*" mode="component.list.of.figures.titlepage.verso.mode">
  <!-- if an element isn't found in this mode, -->
  <!-- try the generic titlepage.mode -->
  <xsl:apply-templates select="." mode="titlepage.mode"/>
</xsl:template>

<xsl:template name="component.list.of.examples.titlepage.recto">
  <fo:block xmlns:fo="http://www.w3.org/1999/XSL/Format" xsl:use-attribute-sets="component.list.of.examples.titlepage.recto.style" space-before.minimum="1em" space-before.optimum="1em" space-before.maximum="1em" space-after="0.5em" margin-left="{$title.margin.left}" font-size="12pt" font-weight="bold" font-family="{$title.fontset}">
<xsl:call-template name="gentext">
<xsl:with-param name="key" select="'ListofExamples'"/>
</xsl:call-template></fo:block>
</xsl:template>

<xsl:template name="component.list.of.examples.titlepage.verso">
</xsl:template>

<xsl:template name="component.list.of.examples.titlepage.separator">
</xsl:template>

<xsl:template name="component.list.of.examples.titlepage.before.recto">
</xsl:template>

<xsl:template name="component.list.of.examples.titlepage.before.verso">
</xsl:template>

<xsl:template name="component.list.of.examples.titlepage">
  <fo:block xmlns:fo="http://www.w3.org/1999/XSL/Format">
    <xsl:variable name="recto.content">
      <xsl:call-template name="component.list.of.examples.titlepage.before.recto"/>
      <xsl:call-template name="component.list.of.examples.titlepage.recto"/>
    </xsl:variable>
    <xsl:variable name="recto.elements.count">
      <xsl:choose>
        <xsl:when test="function-available('exsl:node-set')"><xsl:value-of select="count(exsl:node-set($recto.content)/*)"/></xsl:when>
        <xsl:when test="contains(system-property('xsl:vendor'), 'Apache Software Foundation')">
          <!--Xalan quirk--><xsl:value-of select="count(exsl:node-set($recto.content)/*)"/></xsl:when>
        <xsl:otherwise>1</xsl:otherwise>
      </xsl:choose>
    </xsl:variable>
    <xsl:if test="(normalize-space($recto.content) != '') or ($recto.elements.count &gt; 0)">
      <fo:block><xsl:copy-of select="$recto.content"/></fo:block>
    </xsl:if>
    <xsl:variable name="verso.content">
      <xsl:call-template name="component.list.of.examples.titlepage.before.verso"/>
      <xsl:call-template name="component.list.of.examples.titlepage.verso"/>
    </xsl:variable>
    <xsl:variable name="verso.elements.count">
      <xsl:choose>
        <xsl:when test="function-available('exsl:node-set')"><xsl:value-of select="count(exsl:node-set($verso.content)/*)"/></xsl:when>
        <xsl:when test="contains(system-property('xsl:vendor'), 'Apache Software Foundation')">
          <!--Xalan quirk--><xsl:value-of select="count(exsl:node-set($verso.content)/*)"/></xsl:when>
        <xsl:otherwise>1</xsl:otherwise>
      </xsl:choose>
    </xsl:variable>
    <xsl:if test="(normalize-space($verso.content) != '') or ($verso.elements.count &gt; 0)">
      <fo:block><xsl:copy-of select="$verso.content"/></fo:block>
    </xsl:if>
    <xsl:call-template name="component.list.of.examples.titlepage.separator"/>
  </fo:block>
</xsl:template>

<xsl:template match="*" mode="component.list.of.examples.titlepage.recto.mode">
  <!-- if an element isn't found in this mode, -->
  <!-- try the generic titlepage.mode -->
  <xsl:apply-templates select="." mode="titlepage.mode"/>
</xsl:template>

<xsl:template match="*" mode="component.list.of.examples.titlepage.verso.mode">
  <!-- if an element isn't found in this mode, -->
  <!-- try the generic titlepage.mode -->
  <xsl:apply-templates select="." mode="titlepage.mode"/>
</xsl:template>

<xsl:template name="component.list.of.equations.titlepage.recto">
  <fo:block xmlns:fo="http://www.w3.org/1999/XSL/Format" xsl:use-attribute-sets="component.list.of.equations.titlepage.recto.style" space-before.minimum="1em" space-before.optimum="1em" space-before.maximum="1em" space-after="0.5em" margin-left="{$title.margin.left}" font-size="12pt" font-weight="bold" font-family="{$title.fontset}">
<xsl:call-template name="gentext">
<xsl:with-param name="key" select="'ListofEquations'"/>
</xsl:call-template></fo:block>
</xsl:template>

<xsl:template name="component.list.of.equations.titlepage.verso">
</xsl:template>

<xsl:template name="component.list.of.equations.titlepage.separator">
</xsl:template>

<xsl:template name="component.list.of.equations.titlepage.before.recto">
</xsl:template>

<xsl:template name="component.list.of.equations.titlepage.before.verso">
</xsl:template>

<xsl:template name="component.list.of.equations.titlepage">
  <fo:block xmlns:fo="http://www.w3.org/1999/XSL/Format">
    <xsl:variable name="recto.content">
      <xsl:call-template name="component.list.of.equations.titlepage.before.recto"/>
      <xsl:call-template name="component.list.of.equations.titlepage.recto"/>
    </xsl:variable>
    <xsl:variable name="recto.elements.count">
      <xsl:choose>
        <xsl:when test="function-available('exsl:node-set')"><xsl:value-of select="count(exsl:node-set($recto.content)/*)"/></xsl:when>
        <xsl:when test="contains(system-property('xsl:vendor'), 'Apache Software Foundation')">
          <!--Xalan quirk--><xsl:value-of select="count(exsl:node-set($recto.content)/*)"/></xsl:when>
        <xsl:otherwise>1</xsl:otherwise>
      </xsl:choose>
    </xsl:variable>
    <xsl:if test="(normalize-space($recto.content) != '') or ($recto.elements.count &gt; 0)">
      <fo:block><xsl:copy-of select="$recto.content"/></fo:block>
    </xsl:if>
    <xsl:variable name="verso.content">
      <xsl:call-template name="component.list.of.equations.titlepage.before.verso"/>
      <xsl:call-template name="component.list.of.equations.titlepage.verso"/>
    </xsl:variable>
    <xsl:variable name="verso.elements.count">
      <xsl:choose>
        <xsl:when test="function-available('exsl:node-set')"><xsl:value-of select="count(exsl:node-set($verso.content)/*)"/></xsl:when>
        <xsl:when test="contains(system-property('xsl:vendor'), 'Apache Software Foundation')">
          <!--Xalan quirk--><xsl:value-of select="count(exsl:node-set($verso.content)/*)"/></xsl:when>
        <xsl:otherwise>1</xsl:otherwise>
      </xsl:choose>
    </xsl:variable>
    <xsl:if test="(normalize-space($verso.content) != '') or ($verso.elements.count &gt; 0)">
      <fo:block><xsl:copy-of select="$verso.content"/></fo:block>
    </xsl:if>
    <xsl:call-template name="component.list.of.equations.titlepage.separator"/>
  </fo:block>
</xsl:template>

<xsl:template match="*" mode="component.list.of.equations.titlepage.recto.mode">
  <!-- if an element isn't found in this mode, -->
  <!-- try the generic titlepage.mode -->
  <xsl:apply-templates select="." mode="titlepage.mode"/>
</xsl:template>

<xsl:template match="*" mode="component.list.of.equations.titlepage.verso.mode">
  <!-- if an element isn't found in this mode, -->
  <!-- try the generic titlepage.mode -->
  <xsl:apply-templates select="." mode="titlepage.mode"/>
</xsl:template>

<xsl:template name="component.list.of.procedures.titlepage.recto">
  <fo:block xmlns:fo="http://www.w3.org/1999/XSL/Format" xsl:use-attribute-sets="component.list.of.procedures.titlepage.recto.style" space-before.minimum="1em" space-before.optimum="1em" space-before.maximum="1em" space-after="0.5em" margin-left="{$title.margin.left}" font-size="12pt" font-weight="bold" font-family="{$title.fontset}">
<xsl:call-template name="gentext">
<xsl:with-param name="key" select="'ListofProcedures'"/>
</xsl:call-template></fo:block>
</xsl:template>

<xsl:template name="component.list.of.procedures.titlepage.verso">
</xsl:template>

<xsl:template name="component.list.of.procedures.titlepage.separator">
</xsl:template>

<xsl:template name="component.list.of.procedures.titlepage.before.recto">
</xsl:template>

<xsl:template name="component.list.of.procedures.titlepage.before.verso">
</xsl:template>

<xsl:template name="component.list.of.procedures.titlepage">
  <fo:block xmlns:fo="http://www.w3.org/1999/XSL/Format">
    <xsl:variable name="recto.content">
      <xsl:call-template name="component.list.of.procedures.titlepage.before.recto"/>
      <xsl:call-template name="component.list.of.procedures.titlepage.recto"/>
    </xsl:variable>
    <xsl:variable name="recto.elements.count">
      <xsl:choose>
        <xsl:when test="function-available('exsl:node-set')"><xsl:value-of select="count(exsl:node-set($recto.content)/*)"/></xsl:when>
        <xsl:when test="contains(system-property('xsl:vendor'), 'Apache Software Foundation')">
          <!--Xalan quirk--><xsl:value-of select="count(exsl:node-set($recto.content)/*)"/></xsl:when>
        <xsl:otherwise>1</xsl:otherwise>
      </xsl:choose>
    </xsl:variable>
    <xsl:if test="(normalize-space($recto.content) != '') or ($recto.elements.count &gt; 0)">
      <fo:block><xsl:copy-of select="$recto.content"/></fo:block>
    </xsl:if>
    <xsl:variable name="verso.content">
      <xsl:call-template name="component.list.of.procedures.titlepage.before.verso"/>
      <xsl:call-template name="component.list.of.procedures.titlepage.verso"/>
    </xsl:variable>
    <xsl:variable name="verso.elements.count">
      <xsl:choose>
        <xsl:when test="function-available('exsl:node-set')"><xsl:value-of select="count(exsl:node-set($verso.content)/*)"/></xsl:when>
        <xsl:when test="contains(system-property('xsl:vendor'), 'Apache Software Foundation')">
          <!--Xalan quirk--><xsl:value-of select="count(exsl:node-set($verso.content)/*)"/></xsl:when>
        <xsl:otherwise>1</xsl:otherwise>
      </xsl:choose>
    </xsl:variable>
    <xsl:if test="(normalize-space($verso.content) != '') or ($verso.elements.count &gt; 0)">
      <fo:block><xsl:copy-of select="$verso.content"/></fo:block>
    </xsl:if>
    <xsl:call-template name="component.list.of.procedures.titlepage.separator"/>
  </fo:block>
</xsl:template>

<xsl:template match="*" mode="component.list.of.procedures.titlepage.recto.mode">
  <!-- if an element isn't found in this mode, -->
  <!-- try the generic titlepage.mode -->
  <xsl:apply-templates select="." mode="titlepage.mode"/>
</xsl:template>

<xsl:template match="*" mode="component.list.of.procedures.titlepage.verso.mode">
  <!-- if an element isn't found in this mode, -->
  <!-- try the generic titlepage.mode -->
  <xsl:apply-templates select="." mode="titlepage.mode"/>
</xsl:template>

<xsl:template name="component.list.of.unknowns.titlepage.recto">
  <fo:block xmlns:fo="http://www.w3.org/1999/XSL/Format" xsl:use-attribute-sets="component.list.of.unknowns.titlepage.recto.style" space-before.minimum="1em" space-before.optimum="1em" space-before.maximum="1em" space-after="0.5em" margin-left="{$title.margin.left}" font-size="12pt" font-weight="bold" font-family="{$title.fontset}">
<xsl:call-template name="gentext">
<xsl:with-param name="key" select="'ListofUnknown'"/>
</xsl:call-template></fo:block>
</xsl:template>

<xsl:template name="component.list.of.unknowns.titlepage.verso">
</xsl:template>

<xsl:template name="component.list.of.unknowns.titlepage.separator">
</xsl:template>

<xsl:template name="component.list.of.unknowns.titlepage.before.recto">
</xsl:template>

<xsl:template name="component.list.of.unknowns.titlepage.before.verso">
</xsl:template>

<xsl:template name="component.list.of.unknowns.titlepage">
  <fo:block xmlns:fo="http://www.w3.org/1999/XSL/Format">
    <xsl:variable name="recto.content">
      <xsl:call-template name="component.list.of.unknowns.titlepage.before.recto"/>
      <xsl:call-template name="component.list.of.unknowns.titlepage.recto"/>
    </xsl:variable>
    <xsl:variable name="recto.elements.count">
      <xsl:choose>
        <xsl:when test="function-available('exsl:node-set')"><xsl:value-of select="count(exsl:node-set($recto.content)/*)"/></xsl:when>
        <xsl:when test="contains(system-property('xsl:vendor'), 'Apache Software Foundation')">
          <!--Xalan quirk--><xsl:value-of select="count(exsl:node-set($recto.content)/*)"/></xsl:when>
        <xsl:otherwise>1</xsl:otherwise>
      </xsl:choose>
    </xsl:variable>
    <xsl:if test="(normalize-space($recto.content) != '') or ($recto.elements.count &gt; 0)">
      <fo:block><xsl:copy-of select="$recto.content"/></fo:block>
    </xsl:if>
    <xsl:variable name="verso.content">
      <xsl:call-template name="component.list.of.unknowns.titlepage.before.verso"/>
      <xsl:call-template name="component.list.of.unknowns.titlepage.verso"/>
    </xsl:variable>
    <xsl:variable name="verso.elements.count">
      <xsl:choose>
        <xsl:when test="function-available('exsl:node-set')"><xsl:value-of select="count(exsl:node-set($verso.content)/*)"/></xsl:when>
        <xsl:when test="contains(system-property('xsl:vendor'), 'Apache Software Foundation')">
          <!--Xalan quirk--><xsl:value-of select="count(exsl:node-set($verso.content)/*)"/></xsl:when>
        <xsl:otherwise>1</xsl:otherwise>
      </xsl:choose>
    </xsl:variable>
    <xsl:if test="(normalize-space($verso.content) != '') or ($verso.elements.count &gt; 0)">
      <fo:block><xsl:copy-of select="$verso.content"/></fo:block>
    </xsl:if>
    <xsl:call-template name="component.list.of.unknowns.titlepage.separator"/>
  </fo:block>
</xsl:template>

<xsl:template match="*" mode="component.list.of.unknowns.titlepage.recto.mode">
  <!-- if an element isn't found in this mode, -->
  <!-- try the generic titlepage.mode -->
  <xsl:apply-templates select="." mode="titlepage.mode"/>
</xsl:template>

<xsl:template match="*" mode="component.list.of.unknowns.titlepage.verso.mode">
  <!-- if an element isn't found in this mode, -->
  <!-- try the generic titlepage.mode -->
  <xsl:apply-templates select="." mode="titlepage.mode"/>
</xsl:template>

</xsl:stylesheet>
