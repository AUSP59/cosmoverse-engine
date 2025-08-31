
const path = require('path');
try {
  module.exports = require('node-gyp-build')(path.join(__dirname));
} catch (e) {
  module.exports = {
    version: () => { throw new Error('Addon not built. Run `npm run build`.'); },
    fnv1a64: () => { throw new Error('Addon not built.'); }
  };
}
