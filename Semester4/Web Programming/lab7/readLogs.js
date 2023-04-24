$(function () {
    function refresh() {
        $.getJSON("readLogs.php", {
            severity: $(".settings__severity").val(),
            start_id: parseInt($(".settings__page_number").val()) * 4,
            user: $(".settings__user").val()
        }, json => {
            $(".logs_table__body").empty();
            json.forEach(log => {
                $(".logs_table__body").append(`<tr onclick="window.location='readLog.html?id=${log["id"]}'">   
                    <td>${log["id"]}</td>
                    <td>${log["severity"]}</td>
                    <td>${log["logDate"]}</td>
                    <td>${log["user"]}</td>
                    <td>${log["data"]}</td>
                    <td>
                        <a href="editLog.html?id=${log["id"]}">Edit</a>
                        <a href="deleteLog.html?id=${log["id"]}">Delete</a>
                    </td>
                </tr>`);
            })
        })
    }

    $(".settings__user, .settings__page_number, .settings__severity").on("input", function () {
        refresh();
    })

    $(".settings__previous_button__svg").click(function () {
        let page = parseInt($(".settings__page_number").val()) - 1;
        if (page < 0) {
            page = 0;
        }
        $(".settings__page_number").val(page);
        refresh();
    });

    $(".settings__next_button__svg").click(function () {
        let page = parseInt($(".settings__page_number").val()) + 1;
        $(".settings__page_number").val(page);
        refresh();
    });

    $(".add_log").click(() => {
        window.location = "addLog.html";
    })

    refresh();
});