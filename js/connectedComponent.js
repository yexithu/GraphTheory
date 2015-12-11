var threhold = 0;
var width = window.innerWidth,
    height = window.innerHeight;

var pack = d3.layout.pack()
    			.size([ width, height ])
    			.radius(15);

var svg = d3.select("body").append("svg")
	.attr("id", "c-c-svg")
    .attr("width", width)
    .attr("height", height)
    .append("g")
    .attr("transform", "translate(0,0)");

updateGraph();
var color = d3.scale.category20();

function onThreholdChange()
{
	threhold = document.getElementById('threhold-slider').value;	
	var labelStr = "阈值: " + threhold;
	document.getElementById('thredhold-label').innerHTML = labelStr;
	updateGraph();
}

function getNodeColor(nodeName)
{
	if (nodeName=="Graph") {
		return "rgb(255, 255, 255)";
	}
	if(!isNaN(nodeName)) {
		return color(nodeName);
	}
	return "rgb(31, 119, 180)";
}

function updateGraph()
{
	$("#c-c-svg").remove();
	var svg = d3.select("body").append("svg")
	.attr("id", "c-c-svg")
    .attr("width", width)
    .attr("height", height)
    .append("g")
    .attr("transform", "translate(0,0)");

	var fileName = "json/ConnectedComponents/Threshold" + threhold + ".json";
	console.log(fileName);
	d3.json(fileName, function(error, root) {
	
	var nodes = pack.nodes(root);
	var links = pack.links(nodes);
	
	var node = svg.selectAll("circle")
		.data(nodes)
		.enter()
		.append("circle")
		.attr("fill",function(d) {return getNodeColor(d.name) })
		.attr("fill-opacity","0.4")
		.attr("cx",function(d){
			return d.x;
		})
		.attr("cy",function(d){
			return d.y;
		})
		.attr("r",function(d){
			return d.r;
		})
		.on("mouseover",function(d,i){
			d3.select(this)
				.attr("fill",function(d) { if (d.name == "Graph") { return "rgb(255, 255, 255)";} return "yellow";});
		})
		.on("mouseout",function(d,i){
			d3.select(this)
				.attr("fill",function(d) {return getNodeColor(d.name) });
		});

	node.append("title")
      .text(function(d) { return d.name});
	
	// svg.selectAll("text")
	// 			  .data(nodes)
	// 			  .enter()
	// 			  .append("text")
	// 			  .attr("font-size","3px")
	// 			  .attr("fill","white")
	// 			  .attr("fill-opacity",function(d){
	// 				  if(d.depth == 2)
	// 					  return "0.9";
	// 				  else
	// 					  return "0";
	// 			  })
	// 			  .attr("x",function(d){ return d.x; })
	// 			  .attr("y",function(d){ return d.y; })
	// 			  .attr("dx",-12)
	// 			  .attr("dy",1)
	// 			  .text(function(d){ return d.name; });
	
});
}