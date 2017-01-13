/**
 * Sample React Native App
 * https://github.com/facebook/react-native
 * @flow
 */

import React, { Component } from 'react';
import {
  AppRegistry,
  StyleSheet,
  Text,
  View,
  TouchableNativeFeedback,
  Slider
} from 'react-native';
import BluetoothSerial from 'react-native-bluetooth-serial'
// import Slider from 'react-native-slider';

export default class rn extends Component {
  state = {
    drive: 0,
    steer: 'straight'
  };

  componentWillMount() {
    BluetoothSerial.list().then((devices) => {
      this.setState({devices})
    })
  }

  connect (device) {
    this.setState({ connecting: true })
    BluetoothSerial.connect(device.id)
    .then((res) => {
      this.setState({ device, connected: true, connecting: false })
    })
    .catch((err) => {
      console.error(err)
    })
  }

  steer (where) {
    this.setState({steer: where})

    BluetoothSerial.write(where)
    .then((res) => {
      console.warn('Successfuly wrote to device')
    })
  }

  render() {
    return (
      <View style={styles.wrap}>
        {this.state.connecting && <Text>Connecting...</Text>}
        {!this.state.connected && <View style={styles.listContainer}>
          {this.state.devices && this.state.devices.map((device, i) => {
            return (
              <TouchableNativeFeedback key={i} style={styles.listItem} onPress={this.connect.bind(this, device)}>
                <View style={{ flexDirection: 'row', justifyContent: 'space-between' }}>
                  <Text style={{ fontWeight: 'bold' }}>{device.name}</Text>
                </View>
              </TouchableNativeFeedback>
            )
          })}
        </View>}

        <Text style={styles.text}>
          {this.state.drive && +this.state.drive.toFixed(3)}
        </Text>
        <Slider
          {...this.props}
          minimumValue={-200}
          maximumValue={200}
          minimumTrackTintColor='#1fb28a'
          maximumTrackTintColor='#d3d3d3'
          thumbTintColor='#1a9274'
          step={10}
          onValueChange={(drive) => this.setState({drive: drive})}
        />

        <Text style={styles.text}>
          Now steering: {this.state.steer}
        </Text>

        <View style={styles.steering}>
          <TouchableNativeFeedback background={TouchableNativeFeedback.SelectableBackground()}>
            <View
              style={{width: 150, height: 100, backgroundColor: '#2ecc71'}}
              onTouchStart={this.steer.bind(this, 'left')}
              onTouchEnd={this.steer.bind(this, 'straight')}
            >
              <Text style={{margin: 30}}> Left </Text>
            </View>
          </TouchableNativeFeedback>

          <TouchableNativeFeedback background={TouchableNativeFeedback.SelectableBackground()}>
            <View
              style={{width: 150, height: 100, backgroundColor: '#27ae60'}}
              onTouchStart={this.steer.bind(this, 'right')}
              onTouchEnd={this.steer.bind(this, 'straight')}
            >
              <Text style={{margin: 30}}> Right </Text>
            </View>
          </TouchableNativeFeedback>
        </View>
      </View>
    );
  }
}

const styles = StyleSheet.create({
  wrap: {
    flex: 1,
    justifyContent: 'space-between'
  },
  text: {
    fontSize: 14,
    textAlign: 'center',
    fontWeight: '500',
    margin: 10,
  },
  listContainer: {
    marginTop: 15,
    borderColor: '#ccc',
    borderTopWidth: 0.5
  },
  listItem: {
    flex: 1,
    padding: 10,
    borderColor: '#ccc',
    borderBottomWidth: 0.5
  }
});

AppRegistry.registerComponent('rn', () => rn);
