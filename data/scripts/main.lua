
function onInit()
    local pipeline = ui.newGrid('pipeline')
    pipeline.events.cellClick = function (x, y)
        log.warn('Click: (' .. x .. ', ' .. y .. ')')
    end
    ui.show(pipeline)
end
