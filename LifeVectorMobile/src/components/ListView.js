import React, { Component } from 'react'
import { Text, View, TouchableOpacity, StyleSheet } from 'react-native'
import sample from './../../test.json';

export default class List extends React.Component {


    constructor() {
        super();
        this.state = {
            names: [],
            addresses: [],
            Timespent: [],
            visit: []
        }
        for(var i = 0; i < sample.results.length; i++) {
            this.state.addresses[i] = sample.results[i].address;
            this.state.names[i] = sample.results[i].Name;
            this.state.Timespent[i] = sample.results[i].timespent;
            this.state.visit[i] = sample.results[i].visits;
        }

    }


    alertItemName = (item) => {
        alert("Hi")
    }
    render() {
        return (
            <View>
                {
                    this.state.names((item, index) => (
                        <TouchableOpacity
                            key = {item.id}
                            style = {styles.container}
                            onPress = {() => this.alertItemName(item)}>
                            <Text style = {styles.text}>
                                {item.name}
                            </Text>
                        </TouchableOpacity>
                    ))
                }
            </View>
        )
    }
}

const styles = StyleSheet.create ({
    container: {
        padding: 10,
        marginTop: 3,
        backgroundColor: '#d9f9b1',
        alignItems: 'center',
    },
    text: {
        color: '#4f603c'
    }
})