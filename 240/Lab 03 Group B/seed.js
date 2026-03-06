require('dotenv').config();
const mongoose = require('mongoose');

const Player = require('./models/playerModel');
const Developer = require('./models/developerModel');
const Game = require('./models/gameModel');
const Collaboration = require('./models/collaborationModel');

const playersData = [
    { name: 'John Doe', email: 'john@example.com', age: 25, membershipLevel: 'free' },
    { name: 'Alice Smith', email: 'alice@example.com', age: 30, membershipLevel: 'premium' },
    { name: 'Bob Johnson', email: 'bob@example.com', age: 22, membershipLevel: 'elite' },
    { name: 'Charlie Brown', email: 'charlie@example.com', age: 18, membershipLevel: 'free' },
    { name: 'Diana Prince', email: 'diana@example.com', age: 28, membershipLevel: 'premium' }
];

const developersData = [
    { name: 'Dev One', email: 'dev1@example.com', specializations: ['RPG', 'FPS'], experienceYears: 5, hourlyRate: 30, certifications: ['Unity'] },
    { name: 'Dev Two', email: 'dev2@example.com', specializations: ['Puzzle'], experienceYears: 3, hourlyRate: 20, certifications: ['Unreal Engine'] },
    { name: 'Dev Three', email: 'dev3@example.com', specializations: ['Strategy', 'Simulation'], experienceYears: 8, hourlyRate: 50, certifications: ['AWS', 'Godot'] },
    { name: 'Dev Four', email: 'dev4@example.com', specializations: ['FPS'], experienceYears: 2, hourlyRate: 15, certifications: [] },
    { name: 'Dev Five', email: 'dev5@example.com', specializations: ['RPG', 'Strategy'], experienceYears: 10, hourlyRate: 80, certifications: ['Senior Architect'] }
];

const gamesData = [
    { title: 'Epic Quest', genre: 'RPG', rating: 9, multiplayer: true },
    { title: 'Space Shooter', genre: 'FPS', rating: 7, multiplayer: true },
    { title: 'Mind Boggler', genre: 'Puzzle', rating: 8, multiplayer: false },
    { title: 'Empire Builder', genre: 'Strategy', rating: 9, multiplayer: true },
    { title: 'Farm Life', genre: 'Simulation', rating: 6, multiplayer: false }
];

const seedDatabase = async () => {
    try {
        await mongoose.connect(process.env.MongoDB_URI);
        console.log('Connected to MongoDB');

        // Clear existing data
        await Player.deleteMany();
        await Developer.deleteMany();
        await Game.deleteMany();
        await Collaboration.deleteMany();

        // Insert sample data
        const players = await Player.insertMany(playersData);
        console.log('Players seeded');

        const developers = await Developer.insertMany(developersData);
        console.log('Developers seeded');

        const games = await Game.insertMany(gamesData);
        console.log('Games seeded');

        // Create combinations
        // Requirement is 5 records for each schema
        const collaborationsData = [
            {
                player: players[1]._id, // Alice (premium)
                developer: developers[0]._id, // Dev One (30/hr)
                game: games[0]._id, // Epic Quest
                description: 'Need new weapons added to the game.',
                estimatedHours: 10
            },
            {
                player: players[2]._id, // Bob (elite)
                developer: developers[2]._id, // Dev Three (50/hr)
                game: games[3]._id, // Empire Builder
                description: 'Enhance AI logic for enemies.',
                estimatedHours: 20,
                status: 'accepted',
                cost: 1000 // 20 * 50
            },
            {
                player: players[1]._id,
                developer: developers[1]._id,
                game: games[2]._id,
                description: 'Create new puzzle levels.',
                estimatedHours: 5,
                status: 'in-progress',
                cost: 100
            },
            {
                player: players[4]._id, // Diana (premium)
                developer: developers[4]._id, // Dev Five
                game: games[0]._id,
                description: 'Redesign UI elements',
                estimatedHours: 15
            },
            {
                player: players[2]._id,
                developer: developers[3]._id,
                game: games[1]._id,
                description: 'Fix FPS drops on map 2.',
                estimatedHours: 8,
                status: 'completed',
                cost: 120
            }
        ];

        await Collaboration.insertMany(collaborationsData);
        console.log('Collaborations seeded');

        console.log('Database seeding complete');
        process.exit(0);
    } catch (error) {
        console.error('Error seeding database:', error);
        process.exit(1);
    }
};

seedDatabase();
