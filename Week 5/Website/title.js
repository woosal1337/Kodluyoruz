<!-- Custom Animated Title Made By @woosal1337 -->

function MovingTitle(writeText, interval, visibleLetters) {
    let _instance = {};

    let _currId = 0,
        _numberOfLetters = writeText.length;

    function updateTitle() {
        _currId += 1;
        if (_currId > _numberOfLetters - 1) {
            _currId = 0;
        }

        let startId = _currId,
            endId = startId + visibleLetters,
            finalText;

        if (endId < _numberOfLetters - 1) {
            finalText = writeText.substring(startId, endId);
        } else {
            let cappedEndId = _numberOfLetters;
            endId = endId - cappedEndId;

            finalText = writeText.substring(startId, cappedEndId) + writeText.substring(0, endId);
        }

        document.title = finalText;
    }

    _instance.init = function () {
        setInterval(updateTitle, interval);
    };

    return _instance;
}

let title = new MovingTitle(' @WOOSAL1337 on Social Media', 333, 50);
title.init();
