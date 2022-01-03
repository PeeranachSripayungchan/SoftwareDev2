var firebaseRef = {};
			var firebaseRef1 = {};
			var firebaseRef2 = {};
			var backupdata = {};
			var backupdata1 = {};
			var backupdata2 = {};
			
            
            angular.module('firebaseApp', []).service('firebaseService', function() {
                // สร้าง Function เพื่อ init Firebase เข้ากับ app เรา
                this.initFirebase = function() {
                    var config = {
                        apiKey: "AIzaSyD7URn1Sa7aTmMGkmFJF5OFV-47-i3tLzk",
	                    authDomain: "firealarm-76f2b.firebaseapp.com",
	                    databaseURL: "https://firealarm-76f2b-default-rtdb.firebaseio.com"
                    };
                    firebase.initializeApp(config);
                    firebaseRef = firebase.database().ref("Set1"); 	
					firebaseRef1 = firebase.database().ref("Set2"); 
					firebaseRef2 = firebase.database().ref("Set3");
                }
                // สร้าง Function เพื่อเก็บ event ของ Firebase
                this.eventFirebase = function() {
                    firebaseRef.on('value', function(data) {
                    	const datas = Object.values(data.val());
                		console.log(datas);
                        document.getElementById('temp').innerHTML = 'อุณหภูมิปัจจุบัน : '+ datas[3];
                        document.getElementById('hum').innerHTML = 'ควัน : '+ datas[2];
                        document.getElementById('lux').innerHTML = 'ปิดเปิด : '+ datas[1];
                        document.getElementById('time').innerHTML = 'เวลาแบบ Unix-timestamp ปัจจุบัน : '+ datas[0];
						
                    })
					firebaseRef1.on('value', function(data) {
                    	const datas1 = Object.values(data.val());
                		console.log(datas1);
						backupdata = datas1;
                        document.getElementById('temp1').innerHTML = 'อุณหภูมิปัจจุบัน : '+ backupdata[3];
                        document.getElementById('hum1').innerHTML = 'ควัน : '+ backupdata[2];
                        document.getElementById('lux1').innerHTML = 'ปิดเปิด : '+ backupdata[1];
                        document.getElementById('time1').innerHTML = 'เวลาแบบ Unix-timestamp ปัจจุบัน : '+ backupdata[0];
                    })
					firebaseRef2.on('value', function(data) {
                    	const datas2 = Object.values(data.val());
                		console.log(datas2);
						backupdata1 = datas2;
                        document.getElementById('temp2').innerHTML = 'อุณหภูมิปัจจุบัน : '+ backupdata1[3];
                        document.getElementById('hum2').innerHTML = 'ควัน : '+ backupdata1[2];
                        document.getElementById('lux2').innerHTML = 'ปิดเปิด : '+ backupdata1[1];
                        document.getElementById('time2').innerHTML = 'เวลาแบบ Unix-timestamp ปัจจุบัน : '+ backupdata1[0];
                    })
                }
				


				
				
                this.push = function(title, content) {}
            }).controller('firebaseCtrl', function(firebaseService) {
                // เรียกใช้งาน firebaseService ที่เราสร้างไว้
                firebaseService.initFirebase();
                firebaseService.eventFirebase();
            })