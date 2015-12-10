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

var maxNodeNum = 0;

d3.json("json/graph_nodes.json", function(error, graph) {
  if (error) throw error;
  maxNodeNum = graph.nodes.length;
  force
      .nodes(graph.nodes)
      .links(graph.edges)
      .start();

  var link = svg.selectAll(".link-shortway")
      .data(graph.edges)
    .enter().append("line")
      .attr("class", "link-shortway")
      .style("stroke-width", function(d) { return Math.sqrt(d.weight); });

  var node = svg.selectAll(".node-shortway")
      .data(graph.nodes)
    .enter().append("circle")
      .attr("class", "node-shortway")
      .attr("r", 10)
      .style("fill", function(d) { return color(d.rank); })
      .call(force.drag);

  node.append("title")
      .text(function(d) { return "ID: " + d.id + "\n" + d.title + "\nRank: " + d.rank; });

  force.on("tick", function() {
    link.attr("x1", function(d) { return d.source.x; })
        .attr("y1", function(d) { return d.source.y; })
        .attr("x2", function(d) { return d.target.x; })
        .attr("y2", function(d) { return d.target.y; });

    node.attr("cx", function(d) { return d.x; })
        .attr("cy", function(d) { return d.y; });
  });
});

var start = document.getElementById('startVertex');
var end = document.getElementById('endVertex');

function calculate() {
  if (start.value == "" || end.value == "") {
    alert("请输入要查询的点ID");
    return;
  }
  var startNum = parseInt(start.value);
  var endNum = parseInt(end.value);
  if (startNum >= maxNodeNum || endNum > maxNodeNum) {
    alert("输入溢出");
    return;
  }
  var outputPath = "", weight = 0;
  d3.json(("json/Paths/path" + startNum + ".json"), function(err, res){
    if (err) {
      alert("查询失败");
      return;
    }
    for (var x in res.paths) {
      if (res.paths[x].end == endNum) {
        outputPath = res.paths[x].path;
        weight = res.paths[x].weight;
        break;
      }
    }
    if (weight == -1) {
      document.getElementById("outputPath").value = "两点间不存在路径";
    } else {
      document.getElementById("outputPath").value = "路径：[" + outputPath + "] 长度：" + weight;
    }
  });
}
