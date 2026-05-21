const express = require('express');

const app = express();
const port = 3000;

app.get('*', (req, res) => {
  const xForwardedFor = req.get('x-forwarded-for') || '';

  res.setHeader('Content-Type', 'application/json; charset=utf-8');
  res.end(JSON.stringify({
    receivedBy: 'app',
    path: req.path,
    xForwardedFor,
    remoteAddress: req.socket.remoteAddress,
    allHeaders: req.headers
  }, null, 2));
});

app.listen(port, '0.0.0.0', () => {
  console.log(`XFF test app is listening on ${port}`);
});
