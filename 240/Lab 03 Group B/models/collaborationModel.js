const mongoose = require('mongoose');

const collaborationSchema = new mongoose.Schema({
    player: {
        type: mongoose.Schema.Types.ObjectId,
        ref: 'Player',
        required: true
    },
    developer: {
        type: mongoose.Schema.Types.ObjectId,
        ref: 'Developer',
        required: true
    },
    game: {
        type: mongoose.Schema.Types.ObjectId,
        ref: 'Game',
        required: true
    },
    description: {
        type: String,
        required: true
    },
    estimatedHours: {
        type: Number,
        required: true,
        min: 1
    },
    cost: {
        type: Number,
        default: 0
    },
    status: {
        type: String,
        enum: ['pending', 'accepted', 'in-progress', 'completed', 'cancelled'],
        default: 'pending'
    },
    timeline: {
        type: String
    }
}, { timestamps: true });

module.exports = mongoose.model('Collaboration', collaborationSchema);
