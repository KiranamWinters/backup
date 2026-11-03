return {
    -- Target the core LazyVim noice spec
    {
        "folke/noice.nvim",
        -- Disable it strictly when running inside Neovide
        cond = function()
            return not vim.g.neovide
        end,
    },
}
