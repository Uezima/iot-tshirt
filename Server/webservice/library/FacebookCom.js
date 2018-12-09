module.exports = function(){

    var facebookClient = process.env.FACEBOOK_CLIENT_ID || "* FACEBOOK TOKEN CLIENT_ID *";  
    var facebookAPIEndpoint = 'https://graph.facebook.com/v3.1';
    var facebookPageID = '* FACEBOOK PAGE ID *';

    this.getFacebookCountFans = function(callback){
        
        request(facebookAPIEndpoint + '/' + facebookPageID + '?fields=fan_count&access_token=' + facebookClient, function(err, res, body){
            console.log('response');
            console.log(body);
            callback(res.statusCode, body);
        });
    }

}