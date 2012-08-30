  var dest = Drupal.settings.gbif_stats.forChart;

d3.json(dest, function(data) {
  var width = 895;
  var canvasWidth = 940;
  var height = 420;
  var canvasHeight = 450;
  var padding = 20;
  var barWidth = (width / data.length) - 10;
    
  var x = d3.scale.linear().
    domain([0, data.length]).
    range([0, width]);
  var y = d3.scale.linear().
    domain([0, d3.max(data, function(d) { return d.occurrenceCount + 200000; })]).
    rangeRound([0, height - 100]);
  
  var published = d3.select("#chart").
    append("svg:svg").
    attr("width", canvasWidth).
    attr("height", canvasHeight);

  var barGroup = published.append("svg:g").attr("transform", "translate("+padding+", "+padding+")");
  
  barGroup.selectAll("rect").
    data(data).
    enter().
    append("svg:rect").
    attr("x", function(d, i) { return x(i); }).
    attr("y", height - 100).
    attr("width", barWidth).
    attr("height", 0).
    attr("fill", "#679ED2").
    transition().
      delay(100).
      duration(750).
      attr("height", function(d) { return y(d.occurrenceCount); }).
      attr("y", function(d) { return height - 100 - y(d.occurrenceCount); });
    
  barGroup.selectAll("text").
    data(data).
    enter().
    append("svg:text").
    attr("x", function(d, i) { return x(i); }).
    attr("y", function(d) { return height - 100 - y(d.occurrenceCount); }).
    attr("dx", barWidth/2).
    attr("dy", "-0.4em").
    attr("text-anchor", "middle").
    text(function(d) { return d.occurrenceCount;}).
    attr("style", "font-size: 12; font-family: Helvetica, sans-serif;").
    attr("fill", "grey");

  var yAxis = published.append("svg:g");
    yAxis.selectAll("yAxis").
      data(data).
      enter().append("svg:text").
      attr("x", 0).
      attr("y", 0).
      attr("text-anchor", "end").
      attr("transform", function(d, i){ return "translate("+(x(i)+padding+(barWidth/2))+" "+ (height - 60) +") rotate(-40)";}).
      attr("style", "font-size: 12; font-family: Helvetica, sans-serif;").
      text(function(d) { return d.nodeTitle;}).
      attr("class", "yAxis");

  var rules = published.append("g").attr("transform", "translate("+padding+", "+padding+")");
    rules = rules.selectAll(".rule").
      data(y.ticks(10)).
      enter().append("g").
      attr("class", "rule").
      attr("transform", function(d) { return "translate(0, " + (height -100 - y(d)) + ")"; });
    rules.
      append("line").
      attr("x2", width - 10).
      attr("stroke", "lightgray");
    rules.
      append("text").
      attr("x", width+25).
      attr("dy", ".35em").
      attr("style", "font-size: 12; font-family: Helvetica, sans-serif;").
      attr("text-anchor", "end").
      text(function(d) { return (Math.round(d / 1e5)/10).toFixed(1) + "M"; });
});