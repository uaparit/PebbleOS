<p align="center">
  <img src="docs/_static/images/logo.svg">
</p>

<p align="center">
 PebbleOS 
</p>

<p align="center">
  <a href="https://github.com/coredevices/PebbleOS/actions/workflows/build-firmware.yml?query=branch%3Amain"><img src="https://github.com/coredevices/PebbleOS/actions/workflows/build-firmware.yml/badge.svg?branch=main"></a>
  <a href="https://pebbleos-core.readthedocs.io/en/latest"><img src="https://readthedocs.org/projects/pebbleos-core/badge/?version=latest&style=flat"></a>
  <a href="https://forum.repebble.com/"><img src="https://img.shields.io/discourse/posts?server=https%3A%2F%2Fforum.repebble.com&label=forum"></a>
</p>

> **Fork note (`feat/launcher-text-size`):** personal branch by
> [uaparit](https://github.com/uaparit), based on
> [`v4.36.2`](https://github.com/coredevices/PebbleOS/releases/tag/v4.36.2).
>
> Backported from upstream `main` (not yet in the `4.36.x` release line), 7 commits by Jeff
> Hampton that add the "Text Size" preference (Settings → Display):
> - [`fd4777e58`](https://github.com/coredevices/PebbleOS/commit/fd4777e58) fw/shell: design the ExtraLarge text tier
> - [`a971489be`](https://github.com/coredevices/PebbleOS/commit/a971489be) fw/applib/ui: design ExtraLarge menu cell dimensions
> - [`e6509c418`](https://github.com/coredevices/PebbleOS/commit/e6509c418) fw/applib/ui: honor preferred content size in system menus
> - [`aff65c73a`](https://github.com/coredevices/PebbleOS/commit/aff65c73a) fw/shell/prf: stub out the content size preference
> - [`3c2fe5ff7`](https://github.com/coredevices/PebbleOS/commit/3c2fe5ff7) fw/apps/system/settings: use the standard cell height for the root menu
> - [`d7f2ede0c`](https://github.com/coredevices/PebbleOS/commit/d7f2ede0c) fw/apps/system/settings: move Text Size to Display
> - [`6388ba14f`](https://github.com/coredevices/PebbleOS/commit/6388ba14f) fw: relayout open settings menus on text size change
>
> Added on top: the app launcher (main menu) now follows the same Text Size preference too —
> fonts, row height, and the glance cache size scale with it, matching what the backported
> change already does for system menus.
>
> See the commit history for full details.

## Resources

Here's a quick summary of resources to help you find your way around:

### Getting Started

- 📖 [Documentation](https://pebbleos-core.readthedocs.io/en/latest)
- 🚀 [Prerequisites Guide](https://pebbleos-core.readthedocs.io/en/latest/development/getting_started.html)

### Code and Development

- ⌚ [Source Code Repository](https://github.com/coredevices/PebbleOS)
- 🐛 [Issue Tracker](https://github.com/coredevices/PebbleOS/issues)
- 🤝 [Contribution Guide](CONTRIBUTING.md)

### Community and Support

- 💬 [Discord](https://discordapp.com/invite/aRUAYFN)
- 👥 [Discussions](https://github.com/coredevices/PebbleOS/discussions)
