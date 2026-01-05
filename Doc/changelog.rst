# Changelog

.. _changelog:

NSN (Network Security Navigator) – Project Changelog
===================================================

All notable changes to this project will be documented in this file.

.. note::
   The version numbers follow `Semantic Versioning <https://semver.org/>`_.


Version 0.3.0 – 2026-01-05
--------------------------

- Added comprehensive **benchmark suite** (crypto, network, scan) under ``benchmarks/``.
- Implemented full **security API** documentation (``Doc/api/security.rst``).
- Populated **Android Gradle build script** for NDK compilation.
- Added **CodeQL** static analysis workflow and **Dependabot** configuration.
- Implemented core networking modules: ``socket``, ``dns``, ``tcp``, ``udp``, ``icmp``, ``http``, ``ssh``.
- Implemented security modules: ``scanner``, ``hash``, ``ssl``, ``crypto``.
- Added **GitHub Actions** workflows for build, test, docs, and release.
- Updated CI pipelines for multi‑platform builds (Linux, macOS, Windows).

Version 0.2.0 – 2025-12-20
--------------------------

- Added **standard library** modules for networking, security, and datetime.
- Implemented core object system (int, bool, list, dict, string, ipaddr).
- Added **documentation** skeletons for tutorials, reference, and API.
- Implemented **CI/CD** pipelines (Azure Pipelines templates, GitHub Actions placeholders).
- Added **Docker** packaging scripts and termux subpackages.
- Implemented initial **bytecode evaluator** and compiler scaffolding.

Version 0.1.0 – 2025-11-15
--------------------------

- Project kickoff – repository structure created.
- Core interpreter entry point (``nsn.c``) and basic REPL.
- Initial parser (hand‑written recursive descent) and lexer.
- Basic threading support and traceback handling.
- First commit of README, roadmap, and contribution guidelines.
