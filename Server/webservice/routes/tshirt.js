module.exports = function (app) {

    let facebookCom = new FacebookCom();
    let fanCount = 0;
    let client = null;

    app.get('/tshirt/start', function (req, res) {
        let options = {
            clientId: 'Server',
            username: '* MQTT HOST USER *',
            password: new Buffer('* MQTT HOST PASSWORD *')
        };

        //example: localhost:12345
        client = mqtt.connect('* MQTT HOST URL *:* MQTT HOST PORT *', options);

        client.on('connect', function () {
            client.subscribe('iot-t-shirt/led', function (err) {
                if (!err) {
                    setInterval(function () {
                        sendFanCountMQTT();
                    }, 3000);
                    res.send('Sucesso!');
                } else {
                    res.send('Ocorreu um erro na conexão MQTT');
                }
            })
        })
    })

    this.sendFanCountMQTT = function () {
        facebookCom.getFacebookCountFans(function (statusCode, body) {
            let data = JSON.parse(body);
            if(data.fan_count > fanCount){
                console.log('Enviando mensagem MQTT');
                client.publish('iot-t-shirt/led', 'true');
            }
            fanCount = data.fan_count;
        });
    };
}