
function onInit()
    if ui ~= nil then
        log.info('UI is not nil')
    end
    log.info('Hello, world!')
end

pipeline = {
    onCellClick = function (x, y)
        log.warn('Click: (' .. x .. ', ' .. y .. ')')
    end
}
