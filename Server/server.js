#!/bin/env node

require('./webservice/config/db-library-model.js')();

let app = require('./webservice/config/express.js')();

global.tshirtMode = '0';

let port = 8080;

let server = app.listen(port, function () {
    console.log('Servidor ligado na porta: ' + port);
    
});

//require('./webservice/config/socket.js')(server, app);

