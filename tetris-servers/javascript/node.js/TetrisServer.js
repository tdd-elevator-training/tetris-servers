var log = function(string) {
    console.log(string);
};

var util = require('util');

var hostIp = '127.0.0.1';
var userName = 'apofig';
var protocol = 'WS';

if (protocol == 'HTTP') {
    var http = require('http');
    var url = require('url');

    http.createServer(function (request, response) {
        var p = url.parse(request.url, true).query;

        var answer = answer(p.figure, p.x, p.y, p.glass, p.next);

        response.writeHead(200, {'Content-Type': 'text/plain'});
        response.end(answer);
    }).listen(8888, hostIp);

    log('Server running at http://' + hostIp + ':8888/');
} else {
    var server = 'ws://tetrisj.jvmhost.net:12270/tetris-contest/ws';
    var WebSocket = require('ws');
    var ws = new WebSocket(server + '?user=' + userName);

    ws.on('open', function() {
        log('Opened');
    });

    ws.on('close', function() {
        log('Closed');
    });

    ws.on('message', function(message) {
        log('received: %s', message);

        var pattern = new RegExp(/^figure=(\\w+)&x=(\\d+)&y=(\\d+)&glass=(.*)&next=(\\w*)$/);
        var parameters = message.match(pattern);

        var answer = answer(parameters[1], parameters[2], parameters[3], parameters[4], parameters[5]);

        ws.send(answer);
    });

    log('Web socket client running at http://' + hostIp + ':8080/');
}

var Element = {         // из этих символов состоит строка glass
    EMPTY : ' ',        // так выглядит свободное место в стакане
    BUSY : '*'          // а тут уже занято
}

var DO_NOT_ROTATE = 0;              // не вращать фигурку
var ROTATE_90_CLOCKWISE = 1;        // повернуть по часовой стрелке один раз
var ROTATE_180_CLOCKWISE = 2;       // повернуть по часовой стрелке два раза
var ROTATE_90_COUNTERCLOCKWISE = 3; // повернуть против часовой стрелки 1 раз (3 по часовой)

// метод, говорящий что делать той или иной фигурке figure с координарами x,y в стакане glass. next - очередь следущих фигурок
function answer(figure, x, y, glass, next) {
	// add "drop" to response when you need to drop a figure
	// for details please check http://codenjoy.com/portal/?p=170#commands
	return "left=0, right=0, rotate=0";
}
