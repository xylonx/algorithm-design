/* eslint-disable no-unused-vars */
import { Box } from "@mui/material";
import ReactECharts from "echarts-for-react";
import React from "react";

interface SortProps {
    data: number[][];
    // eslint-disable-next-line no-unused-vars
    sortFunc: (data: number[]) => number;
}

function insertSort(data: number[]): number {
    const start = new Date();
    for (let i = 0; i < data.length; ++i) {
        let minVal = data[i],
            minIdx = i;
        for (let j = i + 1; j < data.length; ++j) {
            if (data[i] < minVal) {
                minVal = data[j];
                minIdx = j;
            }
        }
        data[minIdx] = data[i];
        data[i] = minVal;
    }
    const end = new Date();
    return end.getTime() - start.getTime();
}

function bubbleSort(data: number[]): number {
    const start = new Date();
    for (let i = 0; i < data.length - 1; ++i) {
        for (let j = i + 1; j < data.length; ++j) {
            if (data[j] < data[j - 1]) {
                const tmp = data[j - 1];
                data[j - 1] = data[j];
                data[j] = tmp;
            }
        }
    }
    const end = new Date();
    return end.getTime() - start.getTime();
}

const swap = (input: number[], i: number, j: number) => {
    const tmp = input[i];
    input[i] = input[j];
    input[j] = tmp;
};

const merge = (input: number[], start: number, mid: number, end: number) => {
    // Make a copy of the two subarrays
    const left = input.slice(start, mid + 1);
    const right = input.slice(mid + 1, end + 1);

    let i = 0,
        j = 0,
        k = start;
    while (i < left.length && j < right.length) {
        if (left[i] < right[j]) {
            input[k] = left[i];
            k++;
            i++;
        } else {
            input[k] = right[j];
            k++;
            j++;
        }
    }
    while (k <= end && i < left.length) {
        input[k] = left[i];
        k++;
        i++;
    }
    while (k <= end && j < right.length) {
        input[k] = right[j];
        k++;
        j++;
    }

    return input;
};

function innerMergeSort(input: number[], start: number, end: number): number[] {
    if (end - start <= 1) return [];
    const mid = Math.floor((start + end) / 2);
    innerMergeSort(input, start, mid);
    innerMergeSort(input, mid + 1, end);
    return merge(input, start, mid, end);
}

function mergeSort(data: number[]): number {
    const start = new Date();
    innerMergeSort(data, 0, data.length - 1);
    const end = new Date();
    return end.getTime() - start.getTime();
}

const partition = (input: number[], left: number, right: number): number => {
    const pivot = input[right];
    let minEdge = left - 1;
    for (let i = left; i < right; ++i) {
        if (input[i] <= pivot) {
            minEdge += 1;
            swap(input, i, minEdge);
        }
    }
    swap(input, minEdge + 1, right);
    return minEdge + 1;
};

const quickSortInner = (input: number[], start = 0, end = input.length - 1) => {
    if (start >= end) return;
    const mid = partition(input, start, end);
    quickSortInner(input, start, mid - 1);
    quickSortInner(input, mid + 1, end);

    return input;
};

function quickSort(data: number[]): number {
    const start = new Date();
    quickSortInner(data);
    const end = new Date();
    return end.getTime() - start.getTime();
}

function SortChartComponent(props: SortProps) {
    const options = {
        xAxis: {
            type: "category",
            data: props.data.map((v) => v.length),
        },
        yAxis: {
            type: "value",
        },
        series: [
            {
                data: props.data.map((v) => props.sortFunc(v)),
                type: "line",
            },
        ],
    };

    return <ReactECharts option={options} notMerge={true} lazyUpdate={true}></ReactECharts>;
}

// eslint-disable-next-line no-unused-vars
function constructUnsortedData(size: number): number[] {
    const data = new Array<number>();
    for (let i = 0; i < size; i++) {
        data.push(Math.floor(Math.random() * 1e10));
    }
    return data;
}

export function SortChart() {
    const preData = [];
    for (let i = 0; i < 1e4; i += 200) {
        preData.push(constructUnsortedData(i));
    }

    console.log(quickSortInner(constructUnsortedData(1e4), 0, 19));

    // console.log(quickSort(constructUnsortedData(1e4)));

    return (
        <Box>
            <SortChartComponent data={preData} sortFunc={insertSort}></SortChartComponent>
            <SortChartComponent data={preData} sortFunc={bubbleSort}></SortChartComponent>
            <SortChartComponent data={preData} sortFunc={mergeSort}></SortChartComponent>
        </Box>
    );
}
