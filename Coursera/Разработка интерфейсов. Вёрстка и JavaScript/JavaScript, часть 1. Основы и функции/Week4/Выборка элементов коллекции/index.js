/**
 * @param {Array} collection
 * @params {Function[]} – Функции для запроса
 * @returns {Array}
 */
function query(collection) {
    let functions = [].slice.call(arguments, 1);
    functions.sort();
    let copy = [].slice.call(collection);
    for (let func of functions) {
        copy = func(copy);
    }
    return copy;
}

/**
 * @params {String[]}
 */
function select() {
    let properties = [].slice.call(arguments);
    return function select(collection) {
        return collection.map(item => {
            let newItem = {};
            for (let property of properties) {
                if (item.hasOwnProperty(property)) {
                    newItem[property] = item[property];
                }
            }
            return newItem;
        });
    }
}

/**
 * @param {String} property – Свойство для фильтрации
 * @param {Array} values – Массив разрешённых значений
 */
function filterIn(property, values) {
    return function filterIn(collection) {
        return collection.filter(item => values.indexOf(item[property]) !== -1);
    }
}

module.exports = {
    query: query,
    select: select,
    filterIn: filterIn
};
