/**
 * @param {String[]} hashtags
 * @returns {String}
 */
module.exports = function (hashtags) {
    var tagList = [];
    var tagMap = {};
    for (var i = 0; i < hashtags.length; ++i) {
        var normalized = hashtags[i].toLowerCase();
        if (!tagMap.hasOwnProperty(normalized)) {
            tagMap[normalized] = true;
            tagList.push(normalized);
        }
    }
    return tagList.join(", ");
};
