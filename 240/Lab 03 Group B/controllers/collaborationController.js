const Collaboration = require('../models/collaborationModel');
const Player = require('../models/playerModel');
const Developer = require('../models/developerModel');

const createCollaborationRequest = async (req, res) => {
    const { player, developer, game, description, estimatedHours } = req.body;

    try {
        // Validate player membership
        const playerRecord = await Player.findById(player);
        if (!playerRecord) {
            return res.status(404).json({ error: 'Player not found' });
        }

        if (playerRecord.membershipLevel !== 'premium' && playerRecord.membershipLevel !== 'elite') {
            return res.status(403).json({ error: 'Only premium or elite players can submit customization requests' });
        }

        const newRequest = await Collaboration.create({
            player,
            developer,
            game,
            description,
            estimatedHours
        });

        res.status(201).json(newRequest);
    } catch (error) {
        res.status(400).json({ error: error.message });
    }
};

const updateCollaborationStatus = async (req, res) => {
    const { id } = req.params;
    const { status, timeline } = req.body;

    try {
        const collaboration = await Collaboration.findById(id);

        if (!collaboration) {
            return res.status(404).json({ error: 'Collaboration request not found' });
        }

        // If accepting, calculate the cost
        if (status === 'accepted' && collaboration.status === 'pending') {
            const developer = await Developer.findById(collaboration.developer);
            if (!developer) {
                return res.status(404).json({ error: 'Developer not found' });
            }

            const cost = developer.hourlyRate * collaboration.estimatedHours;
            collaboration.cost = cost;
        }

        if (status) {
            collaboration.status = status;
        }

        if (timeline) {
            collaboration.timeline = timeline;
        }

        await collaboration.save();

        res.status(200).json(collaboration);
    } catch (error) {
        res.status(400).json({ error: error.message });
    }
};

const getCollaborations = async (req, res) => {
    try {
        const collaborations = await Collaboration.find()
            .populate('player', 'name email membershipLevel')
            .populate('developer', 'name email hourlyRate')
            .populate('game', 'title genre');
        res.status(200).json(collaborations);
    } catch (error) {
        res.status(400).json({ error: error.message });
    }
};

module.exports = {
    createCollaborationRequest,
    updateCollaborationStatus,
    getCollaborations
};
