/**
 * @param {Number} hours
 * @param {Number} minutes
 * @param {Number} interval
 * @returns {String}
 */
module.exports = function (hours, minutes, interval) {
    minutes += interval;
    hours += Math.floor(minutes / 60);
    minutes %= 60;
    hours %= 24;
    return ("00" + hours).slice(-2) + ":" + ("00" + minutes).slice(-2);
};
