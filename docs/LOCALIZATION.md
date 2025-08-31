
# Localization
- i18n scaffold uses gettext when `-DCOSMO_I18N=ON` and gettext is available.
- Default language is English; provide `.po` files in `po/` to localize messages.
- Respect common environment variables: `LANG`, `LC_ALL`. CLI avoids color if `NO_COLOR` is set.
