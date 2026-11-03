-- bootstrap lazy.nvim, LazyVim and your plugins
-- Guard clause for Neovide GUI features
--

if vim.g.neovide then
    -- Set your fixed base font (no size modifications will happen here)
    vim.o.guifont = "Iosevka_Term:h15"

    -- Initialize the application scale factor (1.0 = 100%)
    vim.g.neovide_scale_factor = 1.0

    -- Smooth UI scaling helper function
    local function change_scale(amount)
        local new_scale = vim.g.neovide_scale_factor + amount
        -- Clamp scale between 0.5 (50% size) and 3.0 (300% size) to keep it safe
        if new_scale >= 0.5 and new_scale <= 3.0 then
            vim.g.neovide_scale_factor = new_scale
        end
    end

    -- Map to shifted and unshifted variants (Fixes the cursor-forward bug)
    -- Normal Mode
    vim.keymap.set("n", "<C-=>", function()
        change_scale(0.1)
    end, { desc = "Zoom In Canvas" })
    vim.keymap.set("n", "<C-S-=>", function()
        change_scale(0.1)
    end)
    vim.keymap.set("n", "<C-->", function()
        change_scale(-0.1)
    end, { desc = "Zoom Out Canvas" })

    -- Insert Mode
    vim.keymap.set("i", "<C-=>", function()
        change_scale(0.1)
    end)
    vim.keymap.set("i", "<C-S-=>", function()
        change_scale(0.1)
    end)
    vim.keymap.set("i", "<C-->", function()
        change_scale(-0.1)
    end)

    -- Terminal Mode (Bypasses shell navigation sequence issues)
    vim.keymap.set("t", "<C-=>", function()
        change_scale(0.1)
    end)
    vim.keymap.set("t", "<C-S-=>", function()
        change_scale(0.1)
    end)
    vim.keymap.set("t", "<C-->", function()
        change_scale(-0.1)
    end)
end

require("config.lazy")
vim.opt.clipboard = "unnamedplus"

--require("matugen").setup()
