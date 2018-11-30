import React from 'react'
import { Text, View, StyleSheet, processColor } from 'react-native';
import PropTypes from 'prop-types';
import { LineChart } from 'react-native-charts-wrapper';

class Pie extends React.Component {
    constructor() {
        super();

        this.state = {
            legend: {
                enabled: true,
            },
            description: {
                text: 'This is Pie chart description',
                textSize: 15,
                textColor: processColor('darkgray'),
            },
            data: {
                dataSets: [
                    {
                        values: [20, 30, 40]
                        label: 'Users',
                    }
                ],
            }
        };
        for(var i = 0; i < sample.results.length; i++) {
            this.state.data.dataSets[0].values[i] = {'y':frequency};
            this.state.data.dataSets[0].values[i].x = i + 1;
            this.state.data.dataSets[0].values[i].marker = sample.results[i].Name;
            var color = processColor(this.getRandColor(5));
            this.state.legend.custom.colors[i] = color;
            this.state.legend.custom.labels[i] = sample.results[i].Name;
            this.state.data.dataSets[0].config.colors[i] = color;
        }
    }

    render () {
        return (
            <View style={styles.container}>
                <Text style={styles.text}>Frequency of Time Spent</Text>
                <LineChart
                    style={styles.chart}
                    data={this.state.data}
                    width={"100%"}
                    height={"90%"}
                    legend={this.state.legend}
                />
            </View>
        );
    }
}

const styles = StyleSheet.create({
    container: {
        flex: 1,
        backgroundColor: '#F5FCFF'
    },
    chart: {
        flex: 1
    }
});

export default Pie;


