
function onInit()
    log.info('Hello, world!')
end

pipeline = {
    onCellClick = function (x, y)
        log.warn('Click: (' .. x .. ', ' .. y .. ')')
    end
}
