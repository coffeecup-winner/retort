
function onInit()
    ui.show(ui.newGrid('pipeline'))
end

pipeline = {
    onCellClick = function (x, y)
        log.warn('Click: (' .. x .. ', ' .. y .. ')')
    end
}
