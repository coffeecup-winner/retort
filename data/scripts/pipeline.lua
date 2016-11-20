require "scripts/symbol"

local symStart = symbol("start")
local symEnd = symbol("end")
local symPipe = symbol("pipe")

function newPipeline(name)
    local pipeline = ui.newGrid(name)
    pipeline.events.cellClick = function (p, x, y)
        log.warn('Click: (' .. x .. ', ' .. y .. ')')
        setObject(p, x, y, symPipe)
    end
    setObject(pipeline, 4, 4, symStart)
    setObject(pipeline, 5, 4, symPipe)
    setObject(pipeline, 6, 4, symEnd)
    return pipeline
end

function setObject(pipeline, x, y, sym)
    local field = pipeline.data.field
    if (not field) then
        pipeline.data.field = {}
        field = pipeline.data.field
    end
    if not field[x] then
        field[x] = {}
    end
    field[x][y] = sym
end
