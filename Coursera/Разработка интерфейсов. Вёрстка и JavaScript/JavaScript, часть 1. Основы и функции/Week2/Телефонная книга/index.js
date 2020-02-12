// Телефонная книга
var phoneBook = { phonesToNames: {}, namesToPhones: {} };

/**
 * @param {String} command
 * @returns {*} - результат зависит от команды
 */
module.exports = function (command) {
    if (command === "SHOW")
        return show();
    var query = command.slice(command.indexOf(" ") + 1);
    command = command.slice(0, command.indexOf(" "));
    if (command === "ADD")
        addContact(query);
    else if (command === "REMOVE_PHONE")
        return removePhone(query);
};

function addContact(query) {
    var name = query.slice(0, query.indexOf(" "));
    var phones = query.slice(query.indexOf(" ") + 1);
    phones = phones.split(",");
    for (var i = 0; i < phones.length; ++i) {
        if (!phoneBook.namesToPhones.hasOwnProperty(name))
            phoneBook.namesToPhones[name] = [];
        phoneBook.namesToPhones[name].push(phones[i]);
        phoneBook.phonesToNames[phones[i]] = name;
    }
}

function removePhone(phone) {
    let name = phoneBook.phonesToNames[phone];
    if (name == undefined)
        return false;
    delete phoneBook.phonesToNames[phone];
    let index = phoneBook.namesToPhones[name].indexOf(phone);
    phoneBook.namesToPhones[name].splice(index, 1);
    if (phoneBook.namesToPhones[name].length === 0)
        delete phoneBook.namesToPhones[name];
    return true;
}

function show() {
    var result = [];
    let names = Object.keys(phoneBook.namesToPhones);
    names.sort();
    for (var i = 0; i < names.length; ++i) {
        result.push(names[i] + ": " + (phoneBook.namesToPhones[names[i]].join(", ")));
    }
    return result;
}
