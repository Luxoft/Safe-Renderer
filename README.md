# Luxoft Safe-Renderer

[![standard-readme compliant](https://img.shields.io/badge/readme%20style-standard-brightgreen.svg?style=flat-square)](https://github.com/RichardLitt/standard-readme)

Luxoft Safe-Renderer is software tool for rendering Safety Critical HMI.
It is developed as an `SEooC` (acc. to [ISO 26262:2011](https://en.wikipedia.org/wiki/ISO_26262)) in compliance with [ASIL B](https://en.wikipedia.org/wiki/Automotive_Safety_Integrity_Level) level.

Luxoft Safe-Renderer can be used for other types of products or purposes:
- Head units
- Fast graphics engine for instrument cluster/head units
- Other applications

It works in combination with Populus HMI solution and also supports a range of other HMI technologies (e.g. Browser, Kanzi, ...)

Luxoft Safe-Renderer can be used in 2 cases:
1. As fall back renderer: main HMI renders all, Luxoft Safe-Renderer overtakes in "case of failure".
2. Main HMI renderer is used for non-ASIL content, Luxoft Safe-Renderer always for ASIL one.

## Installation

Luxoft Safe-Renderer is configured to be build with [cmake](https://cmake.org/) tool.
You can find `CMakeList.txt` file in the root of the repository.
The building command line for the easiest case will be the following:

    cmake -G your_code_generator ../Safe_Renderer
    make

Safe-Renderer uses several variables for configuration during building.
You can set them within the `cmake` command line arguments:

    cmake -G your_code_generator -DUNIT_TESTS=ON ../Safe_Renderer

The whole list of variables you can find in the `cmake/Variables.cmake` file.

## Usage

After building is finished, you can find Luxoft Safe-Renderer as a static library that you can link to your project.
The header file with exported Safe-Renderer's functions you can find in `engine\psc\psc.h` (***under development***)

## Bugs
Please use 'issues' on GitHub for Luxoft Safe-Renderer.

## Contribute
Patches and pull requests are welcome.

## Copyright and License
Copyright (c) 2018 Luxoft GmbH

This software is licensed under the LGPLv3 to protect Luxoft intellectual property. We are open for discussion about different licensing schemas - just get in contact with us (ARichert@luxoft.com)
