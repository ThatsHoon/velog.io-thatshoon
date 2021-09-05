const axios = require("axios");
const cheerio = require("cheerio");
const dfd = require("danfojs-node");
const tf = require("@tensorflow/tfjs-node");
const data = require("./data.json");
new dfd.DataFrame(data);
