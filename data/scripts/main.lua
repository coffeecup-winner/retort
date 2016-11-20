
function addObject(pipeline, x, y)
    local field = pipeline.data.field
    if (not field) then
        pipeline.data.field = {}
        field = pipeline.data.field
    end
    if not field[x] then
        field[x] = {}
    end
    field[x][y] = {}
end

function onInit()
    local pipeline = ui.newGrid('pipeline')
    pipeline.events.cellClick = function (p, x, y)
        log.warn('Click: (' .. x .. ', ' .. y .. ')')
        addObject(p, x, y)
    end
    ui.show(pipeline)
end
