var graph = [[1, 2, 3], [3], [1, 3], [1], [], [2]];
    var weighted = false;
    var edgesWeight = [
      [1, 2],
      [2, 1, 3],
      [3, 2, 1],
      [1, 2]
    ]; // Example edges weight
    var radius = 200;
    var centerX = 300;
    var centerY = 300;
    var nodes = [];
    var edges = [];

    function setup() {
      createCanvas(600, 600);
      background(255);
      
      // Create nodes
      for (var i = 0; i < graph.length; i++) {
        var angle = (2 * Math.PI / graph.length) * i;
        var x = centerX + radius * Math.cos(angle);
        var y = centerY + radius * Math.sin(angle);
        nodes.push({x: x, y: y, label: i});
      }
      // Create edges
      for (var i = 0; i < graph.length; i++) {
        for (var j = 0; j < graph[i].length; j++) {
            if (weighted) {
                edges.push({start: i, end: graph[i][j], weight: edgesWeight[i][j]});
            } else {
                edges.push({start: i, end: graph[i][j]});
            }
          
        }
      }
    }
    function drawArrow(x1, y1, x2, y2) {
        fill(0, 0, 255);
        var angle = Math.atan2(y2 - y1, x2 - x1);
  var offset = 30;
  push();
  translate(x2 - offset * Math.cos(angle), y2 - offset * Math.sin(angle));
  rotate(angle + Math.PI / 2);
  triangle(-5, 0, 5, 0, 0, -10);
  pop();
}
    function draw() {
      background(255);
      for (var i = 0; i < nodes.length; i++) {
        fill(0);
        ellipse(nodes[i].x, nodes[i].y, 40, 40);
        fill(255);
        text(nodes[i].label, nodes[i].x, nodes[i].y);
    }
      // Draw edges
      stroke(0);
      for (var i = 0; i < edges.length; i++) {
        var start = nodes[edges[i].start];
        var end = nodes[edges[i].end];
        line(start.x, start.y, end.x, end.y);
        drawArrow(start.x, start.y, end.x, end.y);
        var midX = (start.x + end.x) / 2;
        var midY = (start.y + end.y) / 2;
        if (weighted) {
            text(edges[i].weight, midX, midY);
        } 
    }
// Draw nodes
    
    
    }