require "scripts/symbol"

local symStart = symbol("start")
local symEnd = symbol("end")
local symPipe = symbol("pipe")

function newPipeline(name)
    local pipeline = ui.newGrid(name)
    pipeline.data.field = {}
    pipeline.setObject = function (p, i, j, sym)
        local field = p.data.field
        if not field[i] then
            field[i] = {}
        end
        field[i][j] = sym
    end 
    pipeline.events.cellClick = function (p, i, j)
        p:setObject(i, j, symPipe)
    end
    pipeline:setObject(0, 0, symStart)
    pipeline:setObject(1, 0, symPipe)
    pipeline:setObject(2, 0, symEnd)
    return pipeline
end
