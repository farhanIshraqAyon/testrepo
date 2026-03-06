const express = require('express')
const {
    getDevelopers,
    getDeveloper,
    createDeveloper,
    deleteDeveloper,
    updateDeveloper
} = require('../controllers/developerController')

const router = express.Router()

// GET all developers
router.get('/', getDevelopers)

// GET a single developer
router.get('/:id', getDeveloper)

// POST a new developer
router.post('/', createDeveloper)

// DELETE a developer
router.delete('/:id', deleteDeveloper)

// UPDATE a developer
router.patch('/:id', updateDeveloper)

module.exports = router
