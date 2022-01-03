<script src="raphael-2.1.4.min.js"></script>
    <script src="justgage.js"></script>
  <script>
   function notavailable() {
   alert("This function is not available yet.");}
  </script>

  <script>
     document.addEventListener("DOMContentLoaded", function(event) {

       var g1 = new JustGage({
        id: 'g1',
        value: 30,
        title: "อุณหภูมิ",
        titleFontColor : "#505050",
        label: "องศาเซลเซียส",
  titleMinFontSize: 40,
        titleFontFamily: "TH Sarabun New",
        min: 0,
        max: 60,
        pointer: true,
        pointerOptions: {
          toplength: -15,
          bottomlength: 10,
          bottomwidth: 12,
          color: '#8e8e93',
          stroke: '#ffffff',
          stroke_width: 3,
          stroke_linecap: 'round'
        },
        gaugeWidthScale: 0.6,
        counter: true
      });
       var g2 = new JustGage({
        id: 'g2',
        value: 50,
        title: "ความชื้น",
        titleFontColor : "#505050",
         label: "เปอร์เซ็นต์",
         titleMinFontSize: 40,
        titleFontFamily: "TH Sarabun New",
        min: 0,
        max: 100,

        pointer: true,
        pointerOptions: {
          toplength: -15,
          bottomlength: 10,
          bottomwidth: 12,
          color: '#8e8e93',
          stroke: '#ffffff',
          stroke_width: 3,
          stroke_linecap: 'round'
        },
        gaugeWidthScale: 0.6,
        counter: true
      });
        var g3 = new JustGage({
        id: 'g3',
        value: 1500,
        title: "ความเข้มแสง",
        titleFontColor : "#505050",
         label: "ลักซ์",
         titleMinFontSize: 40,
        titleFontFamily: "TH Sarabun New",
        min: 0,
        max: 300000,

        pointer: true,
        pointerOptions: {
          toplength: -15,
          bottomlength: 10,
          bottomwidth: 12,
          color: '#8e8e93',
          stroke: '#ffffff',
          stroke_width: 3,
          stroke_linecap: 'round'
        },
        gaugeWidthScale: 0.6,
        counter: true
      });
        var g4 = new JustGage({
        id: 'g4',
        titleFontColor : "#505050",
        value: 125,
        title: "ปริมาณฝุ่น PM2.5",
         label: "ไมโครกรัมต่อลูกบาศ์กเมตร",
         titleMinFontSize: 40,
        titleFontFamily: "TH Sarabun New",
        min: 0,
        max: 250,

        pointer: true,
        pointerOptions: {
          toplength: -15,
          bottomlength: 10,
          bottomwidth: 12,
          color: '#8e8e93',
          stroke: '#ffffff',
          stroke_width: 3,
          stroke_linecap: 'round'
        },
        gaugeWidthScale: 0.6,
        counter: true
      });
      var g5 = new JustGage({
        id: 'g5',
        titleFontColor : "#505050",
        value: 700,
        title: "ความกดอากาศ",
         label: "เฮกโตปาสกาล",
         titleMinFontSize: 40,
        titleFontFamily: "TH Sarabun New",
        min: 300,
        max: 1100,

        pointer: true,
        pointerOptions: {
          toplength: -15,
          bottomlength: 10,
          bottomwidth: 12,
          color: '#8e8e93',
          stroke: '#ffffff',
          stroke_width: 3,
          stroke_linecap: 'round'
        },
        gaugeWidthScale: 0.6,
        counter: true
      });
      var g6 = new JustGage({
        id: 'g6',
        value: 500,
        titleFontColor : "#505050",
        title: "ปริมาณน้ำฝน",
         label: "มิลลิเมตร",
         titleMinFontSize: 40,
        titleFontFamily: "TH Sarabun New",
        min: 0,
        max: 999,

        pointer: true,
        pointerOptions: {
          toplength: -15,
          bottomlength: 10,
          bottomwidth: 12,
          color: '#8e8e93',
          stroke: '#ffffff',
          stroke_width: 3,
          stroke_linecap: 'round'
        },
        gaugeWidthScale: 0.6,
        counter: true
      });
      var g7 = new JustGage({
        id: 'g7',
        value: 25,
        title: "ความเร็วลม",
        titleFontColor : "#505050",
         label: "เมตรต่อวินาที",
         titleMinFontSize: 40,
        titleFontFamily: "TH Sarabun New",
        min: 0,
        max: 50,

        pointer: true,
        pointerOptions: {
          toplength: -15,
          bottomlength: 10,
          bottomwidth: 12,
          color: '#8e8e93',
          stroke: '#ffffff',
          stroke_width: 3,
          stroke_linecap: 'round'
        },
        gaugeWidthScale: 0.6,
        counter: true
      });
      var g8 = new JustGage({
        id: 'g8',
        value: 180,
        title: "ทิศเหนือ",
        donut: true,
        levelColors : ["#edebeb","#edebeb" ,"#edebeb"],
        titleFontColor : "#505050",
         label: "องศา",
         titleMinFontSize: 40,
        titleFontFamily: "TH Sarabun New",
        min: 0,
        max: 360,

        pointer: true,
        pointerOptions: {
          toplength: -15,
          bottomlength: 10,
          bottomwidth: 12,
          color: '#8e8e93',
          stroke: '#ffffff',
          stroke_width: 3,
          stroke_linecap: 'round'
        },
        gaugeWidthScale: 0.6,
        counter: true
      });
   function notavailable() {
      alert("This function is not available yet.");
   }

    document.getElementById('section1').addEventListener('mousemove', function() {
        g1.refresh(temp_curf);
        g2.refresh(hum_curf);
        g3.refresh(light_curf);
        g4.refresh(pm_curf);
        g5.refresh(pressure_curf);
        g6.refresh(rain_curf);
        g7.refresh(wspeed_curf);
        g8.refresh(wdir_curf);
      });
    });