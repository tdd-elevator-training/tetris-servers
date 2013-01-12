var http = require('http');
var url = require('url') ;
http.createServer(function (request, response) {
    var parameters = url.parse(request.url, true).query;
    var figure = parameters.figure;
    var x = parameters.x;	
    var y = parameters.y;
    var glass = parameters.glass;
    var next = parameters.next;
  
    console.log("Figure: " + figure + ", coordinates: (" + x + ", " + y + "), glass " + glass + ", next " + next);
	
	response.writeHead(200, {'Content-Type': 'text/plain'});
    response.end(answer(figure, x, y, glass, next));
}).listen(8888, '127.0.0.1');
console.log('Server running at http://127.0.0.1:8888/');

var DO_NOT_ROTATE = 0;
var ROTATE_90_CLOCKWISE = 1;
var ROTATE_180_CLOCKWISE = 2;
var ROTATE_90_COUNTERCLOCKWISE = 3;

function answer(figure, x, y, glass, next) {
	// add "drop" to response when you need to drop a figure
	// for details please check http://codenjoy.com/portal/?p=170#commands
	return "left=0, right=0, rotate=0";
}
