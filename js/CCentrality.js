var width = window.innerWidth,
    height = window.innerHeight;

var color = d3.scale.category20();

var force = d3.layout.force()
    .charge(-30)
    .linkDistance(20)
    .size([width, height]);

var svg = d3.select("body").append("svg")
    .attr("width", width)
    .attr("height", height);

var colorGradient = ["#d3fdfb", "#c0e2f8", "#aec8f6", "#9caef4", "#8a94f2", "#7879f0", "#665fee", "#5445ec", "#422bea", "#3011e8"];
var centralityGradient = [1084, 1389, 1513, 1579, 1666, 1763, 1859, 1984, 2088, 2239];

function assignColor(cenVal) {
  var count = 0;
  for (var x in centralityGradient) {
    if (cenVal >= centralityGradient[x]) 
    {
       count = count + 1;    
    }
  }
  return colorGradient[count - 1];
}

d3.json("json/graph_nodes_centrality.json", function(error, graph) {
  if (error) throw error;
  force
      .nodes(graph.nodes)
      .links(graph.edges)
      .start();

  var link = svg.selectAll(".link-centrality")
      .data(graph.edges)
    .enter().append("line")
      .attr("class", "link-centrality")
      .style("stroke-width", function(d) { return Math.sqrt(d.weight); });

  var node = svg.selectAll(".node-centrality")
      .data(graph.nodes)
    .enter().append("circle")
      .attr("class", "node-centrality")
      .attr("r", 10)
      .style("fill", function(d) { return assignColor(d.CCentrality); })
      .call(force.drag);

  node.append("title")
      .text(function(d) { return d.title + "\n中心度: " + d.CCentrality; });

  force.on("tick", function() {
    link.attr("x1", function(d) { return d.source.x; })
        .attr("y1", function(d) { return d.source.y; })
        .attr("x2", function(d) { return d.target.x; })
        .attr("y2", function(d) { return d.target.y; });

    node.attr("cx", function(d) { return d.x; })
        .attr("cy", function(d) { return d.y; });
  });
});