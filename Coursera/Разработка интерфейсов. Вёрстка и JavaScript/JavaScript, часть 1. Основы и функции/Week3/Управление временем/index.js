/**
 * @param {String} date
 * @returns {Object}
 */

const fields = [
    "years",
    "months",
    "days",
    "hours",
    "minutes"
];

function calc(date, type, count, operation) {
    if (operation === "sub")
        count = -count;
    if (type === "years")
        date.setFullYear(date.getFullYear() + count);
    if (type === "months")
        date.setMonth(date.getMonth() + count);
    if (type === "days")
        date.setDate(date.getDate() + count);
    if (type === "hours")
        date.setHours(date.getHours() + count);
    if (type === "minutes")
        date.setMinutes(date.getMinutes() + count);
    return date;
}

module.exports = function (date) {
    let date_obj = {
        _date: new Date(date),
        add: function (count, type) {
            if (count < 0 || fields.indexOf(type) === -1)
                throw TypeError("Incorrect type");
            this._date = calc(this._date, type, count, "add");
            return this;
        },
        subtract: function (count, type) {
            if (count < 0 || fields.indexOf(type) === -1)
                throw TypeError("Incorrect type");
            this._date = calc(this._date, type, count, "sub");
            return this;
        }
    };
    Object.defineProperty(date_obj, "value", {
        get: function () {
            let year = this._date.getFullYear();
            let month = this._date.getMonth() + 1;
            let day = this._date.getDate();
            let hours = this._date.getHours();
            let minutes = this._date.getMinutes();
            if (month < 10)
                month = '0' + month;
            if (day < 10)
                day = '0' + day;
            if (hours < 10)
                hours = '0' + hours;
            if (minutes < 10)
                minutes = '0' + minutes;
            return year + "-" + month + "-" + day + " " + hours + ":" + minutes;
        }
    });
    return date_obj;
};
