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

> **Fork note (`fix/analytics-heartbeat-dls`):** ⚠️ **historical, do not build/flash as-is.**
> Personal branch by [uaparit](https://github.com/uaparit).
>
> This is the original branch behind upstream
> [PR #1853](https://github.com/coredevices/PebbleOS/pull/1853): the native analytics heartbeat
> (DLS tag 87) never reached the companion app because of a dead NULL check in
> `dls_endpoint_open_session` and because the session was created with `buffered=false`, so a
> failed initial `OpenSession` (e.g. BLE not yet up at boot) was never retried.
>
> PR #1853 was merged, but the `buffered=true` switch turned out to have a second-order bug:
> buffered DLS sessions cap items at `DLS_SESSION_MAX_BUFFERED_ITEM_SIZE` (300 bytes), while the
> heartbeat record is ~570 bytes, so `dls_create()` returned `NULL` and
> `PBL_ASSERTN(s_dls_session != NULL)` crashed on every timer fire — an hourly reboot on
> `v4.36.0`. Found by the community
> ([issue #1919](https://github.com/coredevices/PebbleOS/issues/1919)) and reverted upstream
> ([PR #1935](https://github.com/coredevices/PebbleOS/pull/1935), commit `4fc7e1abd`).
>
> **This branch still has the pre-revert code** (`native.c:310` is `buffered=true`) and predates
> the repo's `v4.36.2` re-basing — it is kept only as a record of what was submitted, not as
> something to build. The NULL-check fix (BUG-1) is fine and already correct upstream; the
> `buffered` switch (BUG-2) is not — upstream's reverted state (`buffered=false`) is what's
> actually in `v4.36.2` and in our other branches.

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
