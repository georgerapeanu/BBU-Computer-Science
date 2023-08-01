describe('Visitor sees product overview', () => {
  it('should check that a user can see product entities on the overview', () => {
    cy.visit('/products');
    cy.wait(3000);
    cy.get("table tbody tr").should('have.length.gt', 0);
  })
})