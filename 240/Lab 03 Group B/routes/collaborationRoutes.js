const express = require('express')
const {
    createCollaborationRequest,
    updateCollaborationStatus,
    getCollaborations
} = require('../controllers/collaborationController')

const router = express.Router()

// GET all collaborations
router.get('/', getCollaborations)

// POST a new collaboration request
router.post('/', createCollaborationRequest)

// UPDATE collaboration status (accept/reject/etc)
router.patch('/:id', updateCollaborationStatus)

module.exports = router
