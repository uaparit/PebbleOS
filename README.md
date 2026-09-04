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

> **Fork note (`v4.36.2-ua-branch`):** personal daily-driver branch by
> [uaparit](https://github.com/uaparit), the build actually flashed to the watch. Based on
> [`v4.36.2`](https://github.com/coredevices/PebbleOS/releases/tag/v4.36.2). Released builds are
> tagged `v4.36.2-uaX.Y` on this branch (see
> [Releases](https://github.com/uaparit/PebbleOS/releases)) — the branch name itself doesn't
> carry a patch number, since a new `ua` tag doesn't always mean new commits here (e.g. a
> rebuild with a different compile flag).
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
> Added on top:
> - the app launcher (main menu) now follows Text Size too — fonts, row height, glance cache
>   size, and the Settings glance's battery/charging icons
> - system-menu cell height/font aligned with the launcher's (was mismatched at "Large")
> - the watchface picker now follows Text Size too
> - system option menus (radio-button lists), including the Text Size picker itself, now follow
>   Text Size too
> - the Health app now always cycles between cards (Steps/HR/Sleep), regardless of how it was
>   launched — quick-launching it via a directional button used to exit to the watchface at the
>   list boundary instead of wrapping
>
> See the commit history for full details.

### Text Size screenshots

Captured under QEMU (`qemu_emery`, same 200×228 display as `obelix`/Pebble Time 2), one column
per Text Size setting. "Smaller"/"Default"/"Larger" are the labels shown in the Settings app;
they map to the `PreferredContentSize` tiers `Medium`/`Large`/`ExtraLarge` (`Large` is the
default on rectangular displays).

| | Smaller (`Medium`) | Default (`Large`) | Larger (`ExtraLarge`) |
|---|---|---|---|
| Main menu | ![Main menu, Smaller](docs/_static/images/fork/text-size/medium-main-menu.png) | ![Main menu, Default](docs/_static/images/fork/text-size/large-main-menu.png) | ![Main menu, Larger](docs/_static/images/fork/text-size/extralarge-main-menu.png) |
| Settings menu | ![Settings menu, Smaller](docs/_static/images/fork/text-size/medium-settings-menu.png) | ![Settings menu, Default](docs/_static/images/fork/text-size/large-settings-menu.png) | ![Settings menu, Larger](docs/_static/images/fork/text-size/extralarge-settings-menu.png) |
| Watchfaces menu | ![Watchfaces menu, Smaller](docs/_static/images/fork/text-size/medium-watchfaces-menu.png) | ![Watchfaces menu, Default](docs/_static/images/fork/text-size/large-watchfaces-menu.png) | ![Watchfaces menu, Larger](docs/_static/images/fork/text-size/extralarge-watchfaces-menu.png) |
| Display menu | ![Display menu, Smaller](docs/_static/images/fork/text-size/medium-display-menu.png) | ![Display menu, Default](docs/_static/images/fork/text-size/large-display-menu.png) | ![Display menu, Larger](docs/_static/images/fork/text-size/extralarge-display-menu.png) |
| Bluetooth | ![Bluetooth, Smaller](docs/_static/images/fork/text-size/medium-bluetooth.png) | ![Bluetooth, Default](docs/_static/images/fork/text-size/large-bluetooth.png) | ![Bluetooth, Larger](docs/_static/images/fork/text-size/extralarge-bluetooth.png) |

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
