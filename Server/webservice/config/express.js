#!/bin/env node

module.exports = function () {
    var express = require('express');
    var app = express();

    var bodyParser = require('body-parser');

    app.use(bodyParser.urlencoded({
        extended: false
    }));

    app.use(express.static('./static'));

    require('../routes/tshirt.js')(app);

    return app;
}