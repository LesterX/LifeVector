import React, { Component } from 'react';
import {
    AppRegistry,
    Platform,
    PermissionsAndroid,
    StyleSheet,
    Text,
    View,
    NativeEventEmitter,
    DeviceEventEmitter,
    NativeModules,
    Button,
    ToastAndroid,
    FlatList,
    Alert,
    AppState
} from 'react-native';
import BackgroundTimer from 'react-native-background-timer';
import BLEAndLocation from './BLEAndLocation';
import newBLE from 'react-native-ble-manager';
import { AsyncStorage } from "react-native";
import { bytesToString, stringToBytes } from 'convert-string';
import PushNotification from 'react-native-push-notification';
import PushNotificationAndroid from 'react-native-push-notification';
const uniqueId = require('react-native-unique-id');
const BleManagerModule = NativeModules.BleManager;
const bleManagerEmitter = new NativeEventEmitter(BleManagerModule);

import Spinner from 'react-native-spinkit';
import { BleManager } from 'react-native-ble-plx';
import DeviceInfo from 'react-native-device-info';
import {RSA, RSAKeychain} from 'react-native-rsa-native';



export default class BLEPage extends Component {

    constructor() {
        super();
        this.manager = new BleManager();
        this.manager2 = newBLE;
        this.connectionID = null;
        this.state = {
            is_scanning: false,
            connected_peripheral: null,
            connect_alert: false,
            bl_alert: false,
            appState: AppState.currentState,
            is_connected: false
        };
        this.public_key = null;
        this.private_key = null;
        this.background = null;
        this.bkgdID = null;
        this.timeoutID = null;
        this.dev_id = null;

        this.peripherals = [];

        this.openBox = this.openBox.bind(this);

        this.manager.state()
          .then((result)=>{
            if (result == "PoweredOff"){
              Alert.alert(
                'Bluetooth is turned off',
                'Would you like to turn on bluetooth for this app?',
                [
                  {text: 'OK', onPress: () => {
                      this.manager.enable()
                        .then((message) => {
                          console.log('Bluetooth is already enabled');
                        })
                        .catch((error) => {
                          console.log(error);
                          Alert.alert('You need to enable bluetooth to use this app.', error.message);
                        });
                    }},
                  {text: 'Cancel', onPress: () => {
                    }, style: 'cancel'},
                ],
                { onDismiss: () => {} }
              )
            }
          });



        if(Platform.OS === 'android' && Platform.Version >= 23) {
          PermissionsAndroid.check(PermissionsAndroid.PERMISSIONS.ACCESS_COARSE_LOCATION).then((result) => {
            if (!result) {
              PermissionsAndroid.request(PermissionsAndroid.PERMISSIONS.ACCESS_COARSE_LOCATION).then((result) => {
                if (!result) {
                  Alert.alert('You need to give access to coarse location to use this app.', '');
                }
              });
            }
          });
        }
      this.manager2.start({showAlert: false});
      this.manager2.getConnectedPeripherals([])
        .then((peripheralsArray) => {
          for (var i = 0; i < peripheralsArray.length; i++) {
            if(peripheralsArray[i].name != null && peripheralsArray[i].name.startsWith('lifepi')){
              this.connect(peripheralsArray[i].id, true);
            }
          }
        });
      RSA.generateKeys(4096) // set key size
        .then(keys => {
          AsyncStorage.setItem('public_key', keys.public, () => {
            console.log("Successfully saved public key");
          });
          AsyncStorage.setItem('private_key', keys.private, () => {
            console.log("Successfully saved private key");
          });
        });
      uniqueId()
        .then(id => {
          this.dev_id = id;
        })
        .catch(error => console.error(error))
    }

    componentDidUpdate(prevProps, prevState){
      if (this.state.is_connected !== prevState.is_connected){
        if (this.state.is_connected == true){
          this.manager2.requestMTU(this.state.connected_peripheral, 1000)
            .then ((mtu) => {
              console.log("MTU: " + mtu);
            })
            .catch((error) => {
              console.log("MTU Error: " + error);
            });
          AsyncStorage.getItem('public_key', (err, result) => {
            var sendData = this.dev_id + ":::" + result;
            console.log(sendData);
            // To enable BleManagerDidUpdateValueForCharacteristic listener
            this.manager2.startNotification(this.state.connected_peripheral, '00000001-1E3C-FAD4-74E2-97A033F1BFAA', '00000003-1E3C-FAD4-74E2-97A033F1BFAA')
              .then(() => {
                this.manager2.write(this.state.connected_peripheral, '00000001-1E3C-FAD4-74E2-97A033F1BFAA', '00000003-1E3C-FAD4-74E2-97A033F1BFAA', stringToBytes(sendData), 511)
                  .then((value) => {
                    console.log(String.fromCharCode.apply(null, value));
                  })

              });
          });
        }
      }
    }

    componentWillUnmount(){
      AppState.removeEventListener('change', this._handleAppStateChange);
    }

    connect(device) {
      // Proceed with connection.
      this.manager2.connect(device)
        .then((data) => {
          this.connectionID = setInterval(()=> {
            this.manager2.isPeripheralConnected(device)
              .then((isCOn) => {
                if(!isCOn){
                  this.connect(device);
                } else {
                  this.setState({
                    connected_peripheral: device,
                    is_connected: true,
                    connect_alert: false
                  });
                  clearInterval(this.connectionID);
                }
              })
              .catch((error)=>{});
            this.manager.stopDeviceScan();
          }, 100);

            })
        .catch((error) => {
          this.setState({
            connect_alert: false
          });
        });

    }

  scanAndConnect() {
    this.manager.startDeviceScan(null, {'allowDuplicates': false}, (error, device) => {
      if (error){
        return
      }
      console.log(device.name);
      // Check if it is a device you are looking for based on advertisement data
      // or other criteria.
      if (device != null && device.name != null && device.name.startsWith('lifepi')) {
        // Stop scanning as it's not necessary if you are scanning for one device.
        if (!this.state.connect_alert) {
          this.setState({
            connect_alert: true
          });
          Alert.alert(
            'Server Detected',
            'Would you like to connect to ' + device.name + "?",
            [
              {text: 'OK', onPress: () => {
                  this.connect(device.id);
                }},
              {text: 'Cancel', onPress: () => {
                  this.setState({
                    connect_alert: false
                  });
                }, style: 'cancel'},
            ],
            { onDismiss: () => {this.setState({
                connect_alert: false
              });} }
          )
        }

      }
    })

  }

  checkForScanning(){
      bleManagerEmitter.addListener('BleManagerDiscoverPeripheral', (device)=> {

      });
  }

  backgroundScanCheck() {

    this.manager.state()
      .then((result) => {
        if (result == "PoweredOff") {
          if (!this.state.bl_alert) {
            this.setState({
              bl_alert: true
            });
            Alert.alert(
              'Bluetooth is turned off',
              'Would you like to turn on bluetooth for this app?',
              [
                {
                  text: 'OK', onPress: () => {
                    this.manager.enable()
                      .then((message) => {
                        console.log('Bluetooth is already enabled');
                        this.setState({
                          bl_alert: false
                        });
                      })
                      .catch((error) => {
                        console.log(error);
                        Alert.alert('You need to enable bluetooth to use this app.', error.message);
                        this.setState({
                          bl_alert: false
                        });
                      });
                  }
                },
                {
                  text: 'Cancel', onPress: () => {
                    this.setState({
                      bl_alert: false
                    });
                  }, style: 'cancel'
                },
              ],
              {
                onDismiss: () => {
                  this.setState({
                    bl_alert: false
                  });
                }
              }
            )
          }
        } else {
          if (this.state.connected_peripheral != null) {
            this.manager2.isPeripheralConnected(this.state.connected_peripheral, [])
              .then((isConnected) => {
                if (!isConnected) {
                  this.setState({
                    connected_peripheral: null,
                    is_connected: false
                  });
                  this.scanAndConnect();
                } else {
                  console.log("Device is connected");
                  this.setState({
                    is_connected: true
                  });

                }
              })
              .catch((error) => {})
          } else {
            this.scanAndConnect();
          }
        }
      });
  }



  _handleAppStateChange = (nextAppState) => {
    if (this.state.appState.match(/inactive|background/) && nextAppState === 'active') {
      console.log('App has come to the foreground!');
      try {
        let retValue = this.background.end(this.bkgdID);
        this.manager = retValue.taskData.manager;
        this.setState({connected_peripheral: retValue.taskData.item.state.connected_peripheral, is_connected: retValue.taskData.item.is_connected})
      } catch (error){
        console.log(error);
      } finally {

      }

    } else if (nextAppState == 'background'){
      this.manager.stopDeviceScan();
      this.background = new BLEAndLocation({'timer': BackgroundTimer, 'manager2': this.manager2, 'manager': this.manager, "state": this.state, "item": this});
      this.bkgdID = this.background.start();
    }
    this.setState({appState: nextAppState});

  };

  // componentDidUpdate(){
  //   this.manager.writeCharacteristicWithResponseForService("00000001-1E3C-FAD4-74E2-97A033F1BFAA", "00000003-1E3C-FAD4-74E2-97A033F1BFAA", btoa("hellllly you"))
  //     .then((data) =>{
  //       console.log(data);
  //     });
  // }

  componentDidMount() {
    bleManagerEmitter.addListener(
      'BleManagerDidUpdateValueForCharacteristic',
      ({ value, peripheral, characteristic, service }) => {
        // Convert bytes array to string
        const data = bytesToString(value);
        console.log(`Recieved ${data} for characteristic ${characteristic}`);
      }
    );
    this.checkForScanning();
    AppState.addEventListener('change', this._handleAppStateChange);
    this.timeoutID = setInterval(()=>{this.backgroundScanCheck();},5000);




        // var pusher = new Pusher('YOUR PUSHER APP KEY', {
        //   cluster: 'YOUR PUSHER APP CLUSTER',
        //   encrypted: true
        // });
        //
        // var channel = pusher.subscribe('attendance-channel');
        // channel.bind('attendance-event', (data) => {
        //   if(data.is_attendees){
        //     this.setState({
        //       attendevies: data.attendees
        //     });
        //   }else{
        //     ToastAndroid.show(`${data.full_name} just entered the room!`, ToastAndroid.LONG);
        //     this.setState({
        //       attendees: [...this.state.attendees, data]
        //     });
        //   }
        //
        // });
    }
    disconnect(){
       this.manager2.disconnect(this.state.connected_peripheral)
          .then(() => {
            this.manager.disable()
              .then(() =>{
                this.manager.enable()
                  .then(() =>{
                    this.setState({
                      connected_peripheral: null,
                      is_connected: false
                    });
                  })
                  .catch((error) => {
                    console.log(error);
                  })
              })
          })
          .catch((error) => {
            // Failure code
            console.log(error);
          });
    }




    renderItem({item}) {

        if(item.full_name){           return (
                <View style={styles.list_item} key={item.id}>
                    <Text style={styles.list_item_text}>{item.full_name}</Text>
                    <Text style={styles.list_item_text}>{item.time_entered}</Text>
                </View>
            );
        }

        return (
            <View style={styles.list_item} key={item.id}>
                <Text style={styles.list_item_text}>{item.name}</Text>
                <Button
                    title="Connect"
                    color="#1491ee"
                    style={styles.list_item_button}
                    onPress={this.connect.bind(this, item.id)} />
            </View>
        );
    }


    openBox() {
        this.setState({
            promptVisible: true
        });
    }

    render() {
        return (
            <View style={styles.container}>
                <View style={styles.header}>
                    <View style={styles.app_title}>
                        <Text style={styles.header_text}>Life Vector Mobile</Text>
                    </View>

                </View>

                <View style={styles.body}>

                    <Spinner
                        size={50}
                        type={"WanderingCubes"}
                        color={"#6097FC"}
                        isVisible={this.state.is_scanning}
                        style={styles.spinner}
                    />

                    {
                        !this.state.connected_peripheral &&
                        <FlatList
                            data={this.state.peripherals}
                            renderItem={this.renderItem.bind(this)}
                        />
                    }

                    {
                        this.state.attendees &&
                        <View style={styles.attendees_container}>
                            <Prompt
                                title="Enter your full name"
                                placeholder="e.g. Son Goku"
                                visible={this.state.promptVisible}
                                onCancel={() => {
                                    this.setState({
                                        promptVisible: false
                                    });
                                }
                                }
                                onSubmit={ (value) => {
                                    this.setState({
                                        promptVisible: false
                                    });
                                    this.attend.call(this, value);
                                }
                                }/>
                            {
                                !this.state.has_attended &&
                                <Button
                                    title="Enter"
                                    color="#1491ee"
                                    onPress={this.openBox} />
                            }
                            <FlatList
                                data={this.state.attendees}
                                renderItem={this.renderItem.bind(this)}
                            />
                        </View>
                    }

                </View>
                <View style={styles.header_button_container}>
                  {
                    this.state.connected_peripheral != null && <Button title="DISCONNECT" color="#1491ee" onPress={()=>{this.disconnect(this.state.connected_peripheral);}} />
                  }
                </View>
            </View>
        );
    }
}

const styles = StyleSheet.create({
    container: {
        flex: 1,
        alignSelf: 'stretch',
        backgroundColor: '#F5FCFF',
    },
    header: {
        flex: 1,
        backgroundColor: '#3B3738',
        flexDirection: 'row'
    },
    app_title: {
        flex: 7,
        padding: 10
    },
    header_button_container: {
        flex: 2,
        justifyContent: 'center',
        paddingRight: 5
    },
    header_text: {
        fontSize: 20,
        color: '#FFF',
        fontWeight: 'bold'
    },
    body: {
        flex: 19
    },
    list_item: {
        paddingLeft: 10,
        paddingRight: 10,
        paddingTop: 15,
        paddingBottom: 15,
        marginBottom: 5,
        borderBottomWidth: 1,
        borderBottomColor: '#ccc',
        flex: 1,
        flexDirection: 'row'
    },
    list_item_text: {
        flex: 8,
        color: '#575757',
        fontSize: 18
    },
    list_item_button: {
        flex: 2

    },
    spinner: {
        alignSelf: 'center',
        marginTop: 30
    },
    attendees_container: {
        flex: 1
    }
});

AppRegistry.registerHeadlessTask('BLEAndLocation', () => BLEAndLocation, );
AppRegistry.registerComponent('lifeVectorMobile', () => lifeVectorMobile);
