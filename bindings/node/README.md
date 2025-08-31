
# Node.js N-API bindings
Prereqs: `node`, `npm`, `node-gyp`, and COSMOVERSE shared lib available in the system path (or link flags adjusted in `binding.gyp`).

```bash
cd bindings/node
npm install node-addon-api node-gyp-build
npm run build
node -e "const c=require('./'); console.log(c.version()); console.log(c.fnv1a64(Buffer.from('abc')).toString(16))"
```
