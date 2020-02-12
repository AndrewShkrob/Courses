module.exports = {

    subscribers: {},

    /**
     * @param {String} event
     * @param {Object} subscriber
     * @param {Function} handler
     */
    on: function (event, subscriber, handler) {
        if (!this.subscribers.hasOwnProperty(event))
            this.subscribers[event] = [];
        this.subscribers[event].push({subscriber: subscriber, handler: handler});
        return this;
    },

    /**
     * @param {String} event
     * @param {Object} subscriber
     */
    off: function (event, subscriber) {
        if (!this.subscribers.hasOwnProperty(event))
            return this;
        let newSubs = [];
        for (let i = 0; i < this.subscribers[event].length; ++i) {
            let sub = this.subscribers[event][i];
            if (sub.subscriber !== subscriber)
                newSubs.push(sub);
        }
        if (newSubs.length === 0)
            delete this.subscribers[event];
        else
            this.subscribers[event] = newSubs;
        return this;
    },

    /**
     * @param {String} event
     */
    emit: function (event) {
        if (!this.subscribers.hasOwnProperty(event))
            return this;
        for (let subscriber of this.subscribers[event]) {
            subscriber.handler.call(subscriber.subscriber);
        }
        return this;
    }
};
