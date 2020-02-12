/**
 * @param {String} tweet
 * @returns {String[]}
 */
module.exports = function (tweet) {
    var hashtags = [];
    var start = 0;
    while((index = tweet.indexOf("#", start)) != -1) {
        start = index + 1;
        var end = tweet.indexOf(" ", start);
        if (end == -1)
            hashtags.push(tweet.slice(start));
        else
            hashtags.push(tweet.slice(start, end));
    }
    return hashtags;
};
