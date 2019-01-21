
// Get the data
var data,
  turns,
  NumOfTurns,
  currentTurn = 1;
var slider = document.getElementById('slider');
NumOfTurns = sessionStorage.getItem("NumOfTurns");
turns = +NumOfTurns;



function InitializeSlider(turns) {
  noUiSlider.create(slider, {
    connect: true,
    start: 1,
    keyboard: true,  // same as [keyboard]="true"
    step: 1,
    pageSteps: 10,  // number of page steps, defaults to 10
    range: {
      min: 0,
      max: turns
    },
    pips: {
      mode: 'count',
      density: 0,
      values: turns + 1, //+1 since we're starting from zero
      stepped: true
    }
  });
  slider.noUiSlider.on('change', function () {
    console.log("slider change")
currentTurn = + slider.noUiSlider.get(); 

 if (currentTurn != turns){
   //last turn has no bargains
  loadCurrentTurnData(currentTurn);
  drawNetwork();
}  
    document.getElementById('currentTurn').innerHTML = currentTurn;
   
    drawChart();
    drawLine();

  });

}